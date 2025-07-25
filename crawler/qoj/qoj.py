import re
import sys
import os
import json
from bs4 import BeautifulSoup as bs4
from datetime import datetime, timedelta
from urllib.parse import urljoin
from dotenv import load_dotenv

load_dotenv()

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
            return True

    def login(self):
        username = os.getenv("QOJ_USERNAME")
        password = os.getenv("QOJ_PASSWORD")
        if self.try_login_with_password(username, password):
            self.log("info", "Login successful with username and password.")
            return
        self.log("fatal", "No valid login method found. Please check your credentials.")

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
        contest_page = self.fetch_page_with_browser("https://qoj.ac/contests")

        soup = bs4(contest_page, "html.parser")
        contest_elements = soup.find_all("tr", class_="table-success")

        contest_infos = []
        for contest in contest_elements:
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

            contest_infos.append(contest_info)

        return contest_infos

    def fetch_contests_get_problem_list(self, contest_info, contest_folder):
        """
        Fetch the list of problems in a contest. You can also perform other operations like downloading the contest attachments.
        Return a dictionary with the following required keys:
        - letter: The letter of the problem (e.g., "A", "B", "C", etc.)
        - name: The name of the problem
        - link: The link to the problem page
        """
        contest_name = contest_info["name"]
        contest_link = contest_info["link"]

        # Go into the contest page to fetch more details
        contest_page = self.fetch_page_with_browser(contest_link)

        soup = bs4(contest_page, "html.parser")

        # Download attachments of the contest
        attachment_block = soup.find("div", class_="card border-success top-buffer-lg")
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

        problem_table = soup.find("table", class_="table").find("tbody")
        if not problem_table:
            self.log("error", f"No problem table found for contest {contest_name}.")
            return None
        problem_elements = problem_table.find_all("tr")

        problems_infos = []
        for problem in problem_elements:
            cols = problem.find_all("td")
            if len(cols) < 2:
                continue

            # Create problem folder
            problem_letter = cols[0].text.strip()
            problem_path = os.path.join(contest_folder, "problems", problem_letter)
            os.makedirs(problem_path, exist_ok=True)

            problem_link = urljoin(self.base_url, cols[1].find("a")["href"])
            problem_name = cols[1].text.strip()

            problem_info = {
                "letter": problem_letter,
                "name": problem_name,
                "link": problem_link,
            }
            problems_infos.append(problem_info)
        return problems_infos

    def fetch_contests_get_problem_details(
        self, problem_info, contest_folder, problem_path
    ):
        """
        Fetch the details of a problem in a contest. This includes downloading the problem statement PDF and extracting time/memory limits.
        Return a dictionary based on the problem_info. No additional keys are required.
        """
        problem_link = problem_info["link"]
        problem_name = problem_info["name"]

        problem_page = self.fetch_page_with_browser(problem_link)
        if not problem_page:
            self.log(
                "error",
                f"Failed to fetch problem page {problem_link}.",
            )
            return None

        problem_soup = bs4(problem_page, "html.parser")

        badge_elements = problem_soup.find("div", class_="uoj-content").find_all(
            "span", class_="badge"
        )
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
            return None

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
        return problem_entry

    def fetch_submissions_fetch_source_code(self, entry):
        """
        Fetch the source code of a submission. This method is called in `_update_submission_status`.
        """

        code_page = self.fetch_page_with_browser(entry["submission_link"])
        code_soup = bs4(code_page, "html.parser")
        code = code_soup.find("pre", class_="sh_sourceCode").find("code").get_text()
        return code

    def fetch_submissions_get_submissions(self):
        """
        Fetch the submissions from the website.
        After fetching each submission, call the `_register_submission` method to register the submission. If the return value is True, stop fetching submissions and exit immediately.
        The submission entry should contain the following keys:
        - submission_id: The ID of the submission
        - problem_name: The name of the problem
        - problem_link: The link to the problem page
        - submit_time: The time when the submission was made, in ISO format (YYYY-MM-DDTHH:MM:SS)
        """

        username = os.getenv("QOJ_USERNAME")
        if not username:
            self.log(
                "fatal",
                "Username not found in environment variables. Cannot fetch submissions.",
            )
            return

        # Assuming there are not more than 50 pages of submissions
        for page in range(11, 12):
            self.log("info", f"Start fetching submissions from page {page}.")
            submissions_page = self.fetch_page_with_browser(
                urljoin(self.base_url, f"submissions?submitter={username}&page={page}")
            )
            if not submissions_page:
                self.log("error", f"Failed to fetch submissions page {page}.")
                break

            soup = bs4(submissions_page, "html.parser")
            current_page = (
                soup.find("li", class_="page-item active").find("a").text.strip()
            )
            if current_page != str(page):
                self.log(
                    "info", f"Reached the end of submissions at page {current_page}."
                )
                break

            table_body = soup.find("table", class_="table").find("tbody")
            if not table_body:
                self.log("error", "No submissions found on this page.")
                break
            submission_elements = table_body.find_all("tr")

            for submission in submission_elements:
                cols = submission.find_all("td")
                if len(cols) < 9:
                    self.log(
                        "warning",
                        "Found submission with less than 9 columns, skipping.",
                    )
                    continue

                submission_id = cols[0].text.strip()
                submission_link = urljoin(self.base_url, cols[0].find("a")["href"])

                problem_name = cols[1].text.strip()
                # To extract pure name, re `^#\d+\. (.*)`
                problem_name_pure = re.match(r"^#\d+\. (.*)", problem_name).group(1)
                problem_link = urljoin(self.base_url, cols[1].find("a")["href"])

                # Status format: [number] or [AC ✓] or [status]
                raw_status = cols[3].text.replace(" ✓", "").strip()
                if raw_status.isdigit():
                    status = int(raw_status)
                    if status == 100:
                        status = "AC"
                else:
                    # only preserve uppercase letters
                    status = "".join(c for c in raw_status if c.isupper())

                time = cols[4].text.strip()
                memory = cols[5].text.strip()
                language = cols[6].text.strip()

                submit_time = datetime.strptime(
                    cols[8].text.strip(), "%Y-%m-%d %H:%M:%S"
                )

                submission_entry = {
                    "submission_id": submission_id,
                    "problem_name": problem_name_pure,
                    "status": status,
                    "time": time,
                    "memory": memory,
                    "language": language,
                    "submit_time": submit_time.isoformat(),
                    "problem_link": problem_link,
                    "submission_link": submission_link,
                }
                stop_fetching = self._register_submission(submission_entry)
                if stop_fetching:
                    return

            self.log(
                "info",
                f"Fetched {len(submission_elements)} submissions from page {page}.",
            )


if __name__ == "__main__":
    crawler = QOJCrawler()
    try:
        crawler.log("important", "QOJ Crawler started at " + datetime.now().isoformat())
        crawler.login()
        crawler.fetch_contests()
        crawler.log("info", "Contests fetched successfully.")
        crawler.fetch_submissions()
        crawler.log("info", "Submissions fetched successfully.")
        crawler.log(
            "important",
            "QOJ Crawler finished successfully at " + datetime.now().isoformat(),
        )
    except Exception as e:
        crawler.log("fatal", f"An error occurred: {e}")
    finally:
        crawler.deinit_driver()
