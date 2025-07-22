import sys
import os
import json

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../..")))
from crawler.base import BaseCrawler


class QOJCrawler(BaseCrawler):
    def __init__(
        self, local_log_path="crawler/qoj/log.json", global_log_path="global.log.json"
    ):
        super().__init__("qoj", local_log_path, global_log_path)
        self.min_wait_time = self.config.get("qoj", {}).get(
            "min_wait_time", 1
        )  # wait time after page load
        self.max_wait_time = self.config.get("qoj", {}).get(
            "max_wait_time", 3
        )  # wait time after page load

        self.init_driver()

    def fetch_page_with_browser(self, url):
        self.driver.get(url)
        self.random_sleep()

        html = self.driver.page_source
        return html

    def is_logged_in(self):
        main_page = self.fetch_page_with_browser("https://qoj.ac/")

        # Check if login was successful
        success = self.config.get("qoj", {}).get("username") in main_page
        return success

    def try_login_with_cookie(self, cookie):
        if not cookie:
            self.log("warning", "No cookie provided for login.")
            return False

        self.driver.get("https://qoj.ac/")
        self.random_sleep()

        # Add cookies to the driver
        self.driver.delete_all_cookies()  # Clear existing cookies
        for name, value in cookie.items():
            self.driver.add_cookie({"name": name, "value": value, "domain": "qoj.ac"})
        self.driver.refresh()  # Refresh to apply cookies

        if not self.is_logged_in():
            self.log("warning", "Login failed with provided cookie.")
            return False
        else:
            self.log("info", "Login successful with cookie.")
            return True

    def try_login_with_password(self, username, password):
        self.driver.get("https://qoj.ac/login")
        self.random_sleep()
        self.driver.find_element("name", "username").send_keys(username)
        self.random_sleep()
        self.driver.find_element("name", "password").send_keys(password)
        self.random_sleep()
        self.driver.find_element("id", "button-submit").click()
        self.random_sleep()

        if not self.is_logged_in():
            self.log("fatal", "Login failed with provided credentials.")
            return False
        else:
            self.log("info", "Login successful with username and password.")
            # Save cookies after successful login
            cookies = self.driver.get_cookies()
            cookie_dict = {c["name"]: c["value"] for c in cookies}
            self.credentials.setdefault("qoj", {})["cookie"] = cookie_dict
            with open(self.credentials_path, "w") as f:
                json.dump(self.credentials, f, indent=2)
            return True

    def login(self):
        # Try to login with cookie first
        cookie = self.credentials.get("qoj", {}).get("cookie")
        if self.try_login_with_cookie(cookie):
            return
        # If cookie login fails, try username/password
        username = self.credentials.get("qoj", {}).get("username")
        password = self.credentials.get("qoj", {}).get("password")
        if self.try_login_with_password(username, password):
            return
        self.log("fatal", "No valid login method found. Please check your credentials.")

    def fetch_contests(self):
        # TODO: Implement contest fetching
        pass

    def fetch_submissions(self, since_time=None):
        # TODO: Implement submission fetching
        pass

    def update_local(self, contests, submissions):
        # TODO: Update contests/ folder and log
        pass


if __name__ == "__main__":
    crawler = QOJCrawler()
    crawler.login()

    crawler.deinit_driver()  # Ensure driver is closed after completion
    # Proceed to fetch contests and submissions...
