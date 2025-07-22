import json
import random
import time
from datetime import datetime
import os
import undetected_chromedriver as uc


class BaseCrawler:
    def __init__(
        self,
        platform_name,
        local_log_path,
        global_log_path="crawler/global.log.json",
        config_path="crawler/config.json",
        credentials_path="crawler/credentials.json",
    ):
        self.platform_name = platform_name
        self.local_log_path = local_log_path
        self.global_log_path = global_log_path
        self.config_path = config_path
        self.credentials_path = credentials_path
        self.driver = None
        self.config = self.load_file(self.config_path)
        self.credentials = self.load_file(self.credentials_path)

    def random_sleep(self):
        sleep_time = random.uniform(self.min_wait_time, self.max_wait_time)
        time.sleep(sleep_time)

    def load_file(self, path):
        if os.path.exists(path):
            with open(path, "r") as f:
                return json.load(f)
        return {}

    def init_driver(self):
        options = uc.ChromeOptions()
        # options.add_argument("--headless=new")  # Uncomment for headless mode
        chromedriver_path = "crawler/chromedriver-linux64/chromedriver"
        try:
            self.driver = uc.Chrome(
                options=options, driver_executable_path=chromedriver_path
            )
        except Exception as e:
            self.log("fatal", f"Failed to start Chrome: {e}")

    def deinit_driver(self):
        if self.driver:
            self.driver.quit()
            self.driver = None

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
        self._write_log(self.local_log_path, log_entry)
        # write global log (only for important/error)
        if level in ("important", "error", "fatal"):
            self._write_log(self.global_log_path, log_entry)
        if level == "fatal":
            raise Exception(f"Fatal error in {self.platform_name} crawler: {msg}")

    def _write_log(self, path, entry):
        # ensure file exists and is a json array
        if not os.path.exists(path):
            with open(path, "w") as f:
                json.dump([], f)
        with open(path, "r+") as f:
            try:
                logs = json.load(f)
            except Exception:
                logs = []
            logs.append(entry)
            f.seek(0)
            json.dump(logs, f, indent=2)
            f.truncate()
