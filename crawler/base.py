import base64
import glob
import json
import random
import shutil
import time
from datetime import datetime
import os
import undetected_chromedriver as uc


class BaseCrawler:
    def __init__(self, platform_name, local_log_path):
        self.platform_name = platform_name
        self.repo_dir = "contests"
        self.download_dir = "crawler/downloads"
        self.local_log_path = local_log_path
        self.global_log_path = "crawler/global.log.json"
        self.config_path = "crawler/config.json"
        self.credentials_path = "crawler/credentials.json"
        self.last_update_path = "crawler/last-update.json"
        self.driver = None
        self.credentials = self._load_file(self.credentials_path)

        # Load configuration
        config = self._load_file(self.config_path, default={})
        for key, value in config.get(platform_name, {}).items():
            setattr(self, key, value)

        # If download directory does not exist, create it
        if not os.path.exists(self.download_dir):
            self.log("warning", f"Download directory does not exist, creating it.")
            os.makedirs(self.download_dir)

        self.init_driver()

    def _random_sleep(self):
        sleep_time = random.uniform(self.min_wait_time, self.max_wait_time)
        time.sleep(sleep_time)

    def get_extension_name(self, language):
        language = language.lower()
        if "c++" in language or "cpp" in language:
            return "cpp"
        if "go" in language:
            return "go"
        if "java" in language:
            return "java"
        if "kotlin" in language:
            return "kt"
        if "pascal" in language:
            return "pas"
        if "python" in language:
            return "py"
        if "rust" in language:
            return "rs"
        if language.startswith("c"):
            return "c"
        if language.startswith("d"):
            return "d"
        # fallback
        return "txt"

    def _load_file(self, path, default=[]):
        if not os.path.exists(path):
            self.log("warning", f"File {path} does not exist, creating a new one.")
            with open(path, "w") as f:
                json.dump(default, f)
        with open(path, "r") as f:
            try:
                return json.load(f)
            except Exception:
                return default

    def _write_file(self, path, entry):
        # ensure file exists and is a json object
        if not os.path.exists(path):
            with open(path, "w") as f:
                json.dump({}, f)
        with open(path, "w") as f:
            json.dump(entry, f, indent=2)

    def _append_file(self, path, entry):
        # ensure file exists and is a json array
        if not os.path.exists(path):
            with open(path, "w") as f:
                json.dump([], f)
        with open(path, "r+") as f:
            try:
                lists = json.load(f)
            except Exception:
                lists = []
            lists.append(entry)
            f.seek(0)
            json.dump(lists, f, indent=2)
            f.truncate()

    def init_driver(self):
        options = uc.ChromeOptions()
        # Specify the path to the Chromium executable
        options.binary_location = os.path.abspath("crawler/chrome-linux/chrome")
        # Set preferences
        prefs = {
            "download.prompt_for_download": False,
            "download.directory_upgrade": True,
            "download.default_directory": os.path.abspath(self.download_dir),
            "plugins.always_open_pdf_externally": True,
            "safebrowsing.enabled": False,
        }
        options.add_experimental_option("prefs", prefs)

        options.add_argument("--headless")  # Uncomment for headless mode
        chromedriver_path = os.path.abspath("crawler/chromedriver_linux64/chromedriver")
        try:
            self.driver = uc.Chrome(
                options=options, driver_executable_path=chromedriver_path
            )
        except Exception as e:
            self.log("fatal", f"Failed to start Chromium: {e}")

    def deinit_driver(self):
        if self.driver:
            self.driver.quit()
            self.driver = None

    def fetch_page_with_browser(self, url):
        try:
            self.driver.get(url)
            self._random_sleep()
        except Exception as e:
            self.log("error", f"Failed to fetch page {url}: {str(e)}")
            return ""

        html = self.driver.page_source
        return html

    def _wait_for_download(self, timeout=30):
        for _ in range(timeout):
            files = glob.glob(os.path.join(self.download_dir, "*"))
            finished = [f for f in files if not f.endswith(".crdownload")]
            if finished:
                return finished[0]
            time.sleep(1)
        return None

    def download_file_with_browser(self, url, filename, target_folder):
        # Check if the target folder exists, create it if not
        if not os.path.exists(target_folder):
            self.log(
                "warning", f"Target folder {target_folder} does not exist, creating it."
            )
            os.makedirs(target_folder)

        # Clean up any existing files in the download_dir
        for file in os.listdir(self.download_dir):
            file_path = os.path.join(self.download_dir, file)
            os.remove(file_path)

        self.driver.get(url)
        time.sleep(3)  # Wait for the download to begin

        # Check if download_dir is empty
        if not os.listdir(self.download_dir):
            return False

        downloaded_path = self._wait_for_download()
        if downloaded_path:
            target_path = os.path.join(target_folder, filename)
            shutil.move(downloaded_path, target_path)
            return True
        else:
            self.log("error", f"Timeout waiting for {filename} to download.")
            return False

    def print_to_pdf_with_browser(self, url, filename, target_folder):
        if not os.path.exists(target_folder):
            self.log(
                "warning", f"Target folder {target_folder} does not exist, creating it."
            )
            os.makedirs(target_folder)

        self.driver.get(url)
        self._random_sleep()
        pdf = self.driver.execute_cdp_cmd(
            "Page.printToPDF", {"printBackground": True, "landscape": False}
        )
        with open(os.path.join(target_folder, filename), "wb") as f:
            f.write(base64.b64decode(pdf["data"]))

    def login(self):
        raise NotImplementedError

    def fetch_contests(self):
        raise NotImplementedError

    def fetch_submissions(self, since_time=None):
        raise NotImplementedError

    def log(self, level, msg):
        """
        level: 'info', 'warning', 'important', 'error'
        info/warning -> only local log
        important/error -> local + global log
        """
        log_entry = {
            "time": datetime.now().isoformat(),
            "level": level,
            "platform": self.platform_name,
            "msg": msg,
        }
        # write local log
        self._append_file(self.local_log_path, log_entry)
        # write global log (only for important/error)
        if level in ("important", "error", "fatal"):
            self._append_file(self.global_log_path, log_entry)
        if level == "fatal":
            raise Exception(f"Fatal error in {self.platform_name} crawler: {msg}")
