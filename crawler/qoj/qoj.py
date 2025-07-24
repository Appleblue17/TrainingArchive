from curses.ascii import isdigit
import re
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

        count = 0
        # Extract four columns
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

            """
            Process the contest problems
            """
            # Create problems folder
            problems_folder = os.path.join(contest_folder, "problems")
            os.makedirs(problems_folder)

            # Go into the contest page to fetch more details
            contest_page = self.fetch_page_with_browser(contest_link)

            soup = bs4(contest_page, "html.parser")

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

            problem_table = soup.find("table", class_="table").find("tbody")
            if not problem_table:
                self.log("error", f"No problem table found for contest {contest_name}.")
                continue
            problem_elements = problem_table.find_all("tr")

            problems = []
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
                "date": date.isoformat(),
                "link": contest_link,
                "problems": problems,
            }
            self.contests.append(contest_entry)

            # Write the contest entry to the local file
            self._write_file(self.contests_path, self.contests)

            count += 1
            print("finished index:", contest_name, count)

    def _update_submission_status(self, entry):
        # Try to find it in self.contests by either problem_name or problem_link
        # If found, write it to the contest/problem folder
        # Otherwise, write it to local staged-submissions.json
        ext = self.get_extension_name(entry["language"])
        filename = f"code.{ext}"

        # Check if the problem has been recorded in any contest
        name_and_link_matched = []
        name_matched = []
        for contest in self.contests:
            for prob in contest.get("problems", []):
                if prob["name"] == entry["problem_name"] and prob["link"] == entry.get(
                    "problem_link"
                ):
                    name_and_link_matched.append((contest, prob))
                elif prob["name"] == entry["problem_name"]:
                    name_matched.append((contest, prob))

        if name_and_link_matched:
            found = True
            contest, prob = name_and_link_matched[0]
        elif name_matched:
            found = True
            contest, prob = name_matched[0]
        else:
            found = False

        if found:
            print("found contest:", contest["name"], "problem:", prob["name"])
            problem_folder = os.path.join(
                self.repo_dir,
                f"{contest['date']} {contest['name']}",
                "problems",
                prob["letter"],
            )
            # Get if the problem is solved
            problem_json_path = os.path.join(problem_folder, "problem.json")
            if not os.path.exists(problem_json_path):
                self.log(
                    "error",
                    f"Problem JSON not found for {prob['name']} in {problem_folder}.",
                )
                return False

            with open(problem_json_path, "r", encoding="utf-8") as f:
                problem_json = json.load(f)
            problem_solved = problem_json.get("solved", False)

            # Update "submit_time" and code file
            is_newer = datetime.fromisoformat(
                entry["submit_time"]
            ) > datetime.fromisoformat(
                problem_json.get("submit_time", "1970-01-01T00:00:00")
            )
            if not (entry["status"] != "AC" and problem_solved) and (
                is_newer or (entry.get("status") == "AC" and not problem_solved)
            ):
                problem_json["submit_time"] = entry["submit_time"]

                # Fetch code file
                code_page = self.fetch_page_with_browser(entry["submission_link"])
                code_soup = bs4(code_page, "html.parser")
                code = (
                    code_soup.find("pre", class_="sh_sourceCode")
                    .find("code")
                    .get_text()
                )

                # Update source code file
                os.makedirs(problem_folder, exist_ok=True)
                file_path = os.path.join(problem_folder, filename)
                with open(file_path, "w", encoding="utf-8") as f:
                    f.write(code)

                # Update code.{ext}.json
                self._write_file(
                    os.path.join(problem_folder, f"code.{ext}.json"),
                    entry,
                )

            # Update problem.json "solved" and "solve_time"
            if entry["status"] == "AC":
                problem_json["solved"] = True

                # If problem_json["solve_time"] is not set or later than entry["submit_time"], update it
                if "solve_time" not in problem_json or datetime.fromisoformat(
                    entry["submit_time"]
                ) < datetime.fromisoformat(
                    problem_json.get("solve_time", "1970-01-01T00:00:00")
                ):
                    problem_json["solve_time"] = entry["submit_time"]

            self._write_file(problem_json_path, problem_json)
            return True

        # If not found, update to staged-submissions.json
        if not found:
            # Check if the problem already exists in staged submissions
            for staged_entry in self.staged_submissions:
                if staged_entry["problem_name"] == entry["problem_name"]:
                    if (
                        entry["status"] == "AC"
                        or not staged_entry.get("status") == "AC"
                    ):
                        # Update the existing entry with the new submission
                        staged_entry.update(entry)
                    break
            else:
                self.staged_submissions.append(entry)
                self._write_file(self.submissions_path, self.staged_submissions)
            return False

    def fetch_submissions(self):
        username = self.credentials.get("qoj", {}).get("username")
        if not username:
            self.log(
                "fatal", "Username not found in credentials. Cannot fetch submissions."
            )
            return

        # Extract staged submissions
        self.last_update = self._load_file(self.last_update_path, default={})
        last_crawled_id = self.last_update.get("qoj", {}).get("id", None)

        self.contests = self._load_file(self.contests_path)
        self.staged_submissions = self._load_file(self.submissions_path)

        # First try updating existing staged submissions
        new_staged = []
        for entry in self.staged_submissions:
            if not self._update_submission_status(entry):
                new_staged.append(entry)
        self.staged_submissions = new_staged
        self._write_file(self.submissions_path, self.staged_submissions)

        finished = False
        for page in range(
            60, 61
        ):  # Assuming there are not more than 1000 pages of submissions
            print("start fetching page:", page)
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
                last_update_time_str = self.last_update.get("qoj", {}).get(
                    "time", "1970-01-01T00:00:00"
                )
                last_update_time = datetime.fromisoformat(last_update_time_str)
                # if submit_time < last_update_time:
                #     self.log(
                #         "info",
                #         f"Reached last update (Submission {submission_id}), stopping.",
                #     )
                #     finished = True
                #     break

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
                self._update_submission_status(submission_entry)
                last_crawled_id = submission_id

            print(f"finished: {page}")
            if finished:
                break

        # Write staged submissions to file

        self.last_update["qoj"] = {
            "time": datetime.now().isoformat(),
            "id": last_crawled_id,
        }
        self._write_file(self.last_update_path, self.last_update)


if __name__ == "__main__":
    crawler = QOJCrawler()
    try:
        crawler.login()
        # crawler.fetch_contests()
        crawler.fetch_submissions()
        crawler.log("info", "Work completed successfully.")
    except Exception as e:
        crawler.log("fatal", f"An error occurred: {e}")
    finally:
        crawler.deinit_driver()
