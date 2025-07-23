import sys
import os
import json
from bs4 import BeautifulSoup as bs4
from datetime import datetime, timedelta
from urllib.parse import urljoin

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../..")))
from crawler.base import BaseCrawler


class QOJCrawler(BaseCrawler):
    def __init__(self, local_log_path="crawler/qoj/log.json"):
        super().__init__("qoj", local_log_path)
        self.contests_path = "crawler/qoj/contests.json"
        self.submissions_path = "crawler/qoj/staged-submissions.json"

    def is_logged_in(self):
        main_page = self.fetch_page_with_browser("https://qoj.ac/")

        # Check if login was successful
        success = self.username in main_page
        return success

    def try_login_with_cookies(self, cookies):
        if not cookies:
            self.log("warning", "No cookies provided for login.")
            return False

        self.driver.get("https://qoj.ac/")
        self._random_sleep()

        # Add cookies to the driver
        self.driver.delete_all_cookies()  # Clear existing cookies
        for name, value in cookies.items():
            self.driver.add_cookie({"name": name, "value": value, "domain": "qoj.ac"})
        self.driver.refresh()  # Refresh to apply cookies

        if not self.is_logged_in():
            self.log("warning", "Login failed with provided cookies.")
            return False
        else:
            return True

    def try_login_with_password(self, username, password):
        self.driver.get("https://qoj.ac/login")
        self._random_sleep()
        self.driver.find_element("name", "username").send_keys(username)
        self._random_sleep()
        self.driver.find_element("name", "password").send_keys(password)
        self._random_sleep()
        self.driver.find_element("id", "button-submit").click()
        self._random_sleep()

        if not self.is_logged_in():
            self.log("fatal", "Login failed with provided credentials.")
            return False
        else:
            # Save cookies after successful login
            cookies = self.driver.get_cookies()
            cookie_dict = {c["name"]: c["value"] for c in cookies}
            self.cookies = cookie_dict
            self.credentials.setdefault("qoj", {})["cookies"] = cookie_dict
            with open(self.credentials_path, "w") as f:
                json.dump(self.credentials, f, indent=2)
            return True

    def login(self):
        # Try to login with cookies first
        self.cookies = self.credentials.get("qoj", {}).get("cookies")
        if self.try_login_with_cookies(self.cookies):
            self.log("info", "Login successful with cookies.")
            return
        # If cookies login fails, try username/password
        username = self.credentials.get("qoj", {}).get("username")
        password = self.credentials.get("qoj", {}).get("password")
        if self.try_login_with_password(username, password):
            self.log("info", "Login successful with username and password.")
            return
        self.log("fatal", "No valid login method found. Please check your credentials.")

    def fetch_contests(self):
        # First read local contests file
        self.contests = self._load_file(self.contests_path)

        # Then fetch contests from the website
        contest_page = self.fetch_page_with_browser("https://qoj.ac/contests")

        soup = bs4(contest_page, "html.parser")
        contest_elements = soup.find_all("tr", class_="table-success")

        # Extract four columns
        for contest in contest_elements[-3:]:
            cols = contest.find_all("td")
            if len(cols) < 4:
                self.log("warning", "Found contest with less than 4 columns, skipping.")
                continue

            # Contest link is the first href in cols[0]
            contest_link = urljoin(self.base_url, cols[0].find("a")["href"])
            contest_name = cols[0].find("a").text.strip()

            # If the contest already exists, skip it
            if any(c["link"] == contest_link for c in self.contests):
                continue

            # Contest start time is in cols[1]
            # Format: YYYY-MM-DD HH:MM:SS
            contest_start_time = cols[1].find("a").text.strip()
            start_time = datetime.strptime(contest_start_time, "%Y-%m-%d %H:%M:%S")
            date = start_time.date()

            # Contest duration is in cols[2]
            # Format: [X hours] or [X hours Y minutes]
            contest_duration = cols[2].text.strip()
            hours = contest_duration.split("hours")[0].strip()
            minutes = (
                contest_duration.split("hours")[1].split("minutes")[0].strip()
                if "minutes" in contest_duration
                else "0"
            )
            # Calculate the end time
            end_time = start_time + timedelta(hours=int(hours), minutes=int(minutes))

            # Difficulty is in cols[3]
            # Format: [?] or [★★★★★] or [★★★☆]; ★=1, ☆=0.5
            difficulty_text = cols[3].text.strip()
            if difficulty_text == "?":
                difficulty = None
            else:
                difficulty = 0
                for char in difficulty_text:
                    if char == "★":
                        difficulty += 1
                    elif char == "☆":
                        difficulty += 0.5

            # Create contest folder
            contest_folder = os.path.join(self.repo_dir, f"{date} {contest_name}")
            if os.path.exists(contest_folder):
                self.log(
                    "warning",
                    f"Contest folder already exists: {contest_folder}. Skipped.",
                )
                continue
            else:
                os.makedirs(contest_folder)
                self.log("info", f"Created contest folder: {contest_folder}")

            # Write contest entry to contest.json
            contest_info = {
                "name": contest_name,
                "date": date.isoformat(),
                "platform": self.platform_name,
                "start_time": start_time.isoformat(),
                "end_time": end_time.isoformat(),
                "link": contest_link,
            }
            if difficulty is not None:
                contest_info["difficulty"] = difficulty
            self._write_file(
                os.path.join(contest_folder, "contest.json"),
                contest_info,
            )

            # Download attachments of the contest
            attachment_block = soup.find(
                "div", class_="card border-success top-buffer-lg"
            )
            if attachment_block:
                attachment_elements = attachment_block.find_all("a")
                for attachment in attachment_elements:
                    attachment_link = urljoin(contest_link, attachment["href"])
                    attachment_name = attachment.text.strip()
                    # Save the attachment to contest_folder
                    attachment_path = urljoin(contest_folder, attachment_name)
                    if not self.download_file_with_browser(
                        attachment_link, attachment_name + ".pdf", contest_folder
                    ):
                        # If download failed or the link is not a download link, print it to pdf
                        self.print_to_pdf_with_browser(
                            attachment_link, attachment_name + ".pdf", contest_folder
                        )
            print("Attachments fetched")

            """
            Process the contest problems
            """
            # Create problems folder
            problems_folder = os.path.join(contest_folder, "problems")
            os.makedirs(problems_folder)

            # Go into the contest page to fetch more details
            contest_page = self.fetch_page_with_browser(contest_link)

            soup = bs4(contest_page, "html.parser")
            problem_table = soup.find("table", class_="table")
            if not problem_table:
                self.log("error", f"No problem table found for contest {contest_name}.")
                continue
            problem_elements = problem_table.find_all("tr")
            problems = []
            for problem in problem_elements[:3]:
                cols = problem.find_all("td")
                if len(cols) < 2:
                    continue
                problem_letter = cols[0].text.strip()
                problem_path = os.path.join(contest_folder, "problems", problem_letter)
                problem_link = urljoin(self.base_url, cols[1].find("a")["href"])
                problem_name = cols[1].text.strip()

                problems.append((problem_name, problem_link))

                problem_page = self.fetch_page_with_browser(problem_link)
                if not problem_page:
                    self.log(
                        "error",
                        f"Failed to fetch problem page {problem_link}.",
                    )
                    continue

                problem_soup = bs4(problem_page, "html.parser")

                badge_elements = problem_soup.find(
                    "div", class_="uoj-content"
                ).find_all("span", class_="badge")
                for badge in badge_elements:
                    badge_content = badge.text.strip()
                    if "Time Limit" in badge_content:
                        time_limit = badge_content.split(":")[1].strip()
                    if "Memory Limit" in badge_content:
                        memory_limit = badge_content.split(":")[1].strip()

                problem_pdf = problem_soup.find("iframe", id="statements-pdf")
                if not problem_pdf:
                    self.log(
                        "error",
                        f"Did not find pdf in {problem_link}.",
                    )
                    continue

                problem_pdf_link = urljoin(self.base_url, problem_pdf["src"].strip())
                if not self.download_file_with_browser(
                    problem_pdf_link, "statement.pdf", problem_path
                ):
                    self.log(
                        "error",
                        f"Failed to download pdf from {problem_pdf_link}.",
                    )

                problem_entry = {
                    "link": problem_link,
                    "name": problem_name,
                }
                if "time_limit" in locals():
                    problem_entry["time_limit"] = time_limit
                if "memory_limit" in locals():
                    problem_entry["memory_limit"] = memory_limit
                problem_entry["solved"] = False

                self._write_file(
                    os.path.join(problem_path, "problem.json"), problem_entry
                )

            print("Problems fetched")

            # Create contest entry
            contest_entry = contest_info
            contest_entry["problems"] = problems
            self.contests.append(contest_entry)

            # Write the contest entry to the local file
            self._append_file(self.contests_path, contest_entry)

    def fetch_submissions(self, since_time=None):
        # TODO: Implement submission fetching
        pass


if __name__ == "__main__":
    crawler = QOJCrawler()
    crawler.login()
    print("Login successful")
    crawler.fetch_contests()

    crawler.deinit_driver()  # Ensure driver is closed after completion
    # Proceed to fetch contests and submissions...
