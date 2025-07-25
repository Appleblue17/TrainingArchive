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

    def login(self):
        raise NotImplementedError

    def fetch_contests_get_contest_list(self):
        """
        Fetch the list of contests from the website, and return a list of contest information.
        Return a dictionary with the following required keys:
        - name: The name of the contest
        - date: The date of the contest in ISO format (YYYY-MM-DD)
        - platform: The platform name (in this case, "QOJ")
        - start_time: The start time of the contest in ISO format (YYYY-MM-DDTHH:MM:SS)
        - end_time: The end time of the contest in ISO format (YYYY-MM-DDTHH:MM:SS)
        - link: The link to the contest
        """
        raise NotImplementedError

    def fetch_contests_get_problem_list(self, contest_info, contest_folder):
        """
        Fetch the list of problems in a contest. You can also perform other operations like downloading the contest attachments.
        Return a dictionary with the following required keys:
        - letter: The letter of the problem (e.g., "A", "B", "C", etc.)
        - name: The name of the problem
        - link: The link to the problem page
        """
        raise NotImplementedError

    def fetch_contests_get_problem_details(
        self, problem_info, contest_folder, problem_path
    ):
        """
        Fetch the details of a problem in a contest. This includes downloading the problem statement PDF and extracting time/memory limits.
        Return a dictionary based on the problem_info. No additional keys are required.
        """
        raise NotImplementedError

    def fetch_contests(self):
        # First read local contests file
        self.contests = self._load_file(self.contests_path)

        # Then fetch contests from the website
        contest_list = self.fetch_contests_get_contest_list()

        count = 0
        for contest_info in contest_list[:1]:
            contest_name = contest_info["name"]
            contest_date = contest_info["date"]
            contest_link = contest_info["link"]

            # Create contest folder
            contest_folder = os.path.join(
                self.repo_dir, f"{contest_date} {contest_name}"
            )
            if os.path.exists(contest_folder):
                self.log(
                    "warning",
                    f"Contest folder already exists: {contest_folder}. Skipped.",
                )
                continue
            else:
                os.makedirs(contest_folder)
                self.log("info", f"Created contest folder: {contest_folder}")

            self._write_file(
                os.path.join(contest_folder, "contest.json"),
                contest_info,
            )

            """
            Process the contest problems
            """
            # Create problems folder
            problems_folder = os.path.join(contest_folder, "problems")
            os.makedirs(problems_folder)

            problem_list = self.fetch_contests_get_problem_list(
                contest_info, contest_folder
            )
            if not problem_list:
                self.log(
                    "error",
                    f"Failed to fetch problem list for contest {contest_name}. Skipping.",
                )
                continue

            problems = []
            for problem_info in problem_list[:2]:
                # Create problem folder
                problem_letter = problem_info["letter"]
                problem_path = os.path.join(contest_folder, "problems", problem_letter)
                os.makedirs(problem_path, exist_ok=True)

                problem_link = problem_info["link"]
                problem_name = problem_info["name"]

                problem_entry = self.fetch_contests_get_problem_details(
                    problem_info, contest_folder, problem_path
                )
                if not problem_entry:
                    self.log(
                        "error",
                        f"Failed to fetch problem details for {problem_name} in {contest_name}.",
                    )
                    continue
                problem_entry["solved"] = False

                problems.append(
                    {
                        "letter": problem_letter,
                        "name": problem_name,
                        "link": problem_link,
                        "solved": False,
                    }
                )
                # Write problem.json
                self._write_file(
                    os.path.join(problem_path, "problem.json"), problem_entry
                )

            # Create contest entry
            contest_entry = {
                "name": contest_name,
                "date": contest_date,
                "link": contest_link,
                "problems": problems,
            }
            self.contests.append(contest_entry)

            # Write the contest entry to the local file
            self._write_file(self.contests_path, self.contests)

            count += 1
            print("finished index:", contest_name, count)

    def fetch_submissions(self, since_time=None):
        raise NotImplementedError
