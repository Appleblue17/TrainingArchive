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
        self.last_update_path = "crawler/last-update.json"
        self.driver = None

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

        for contest_info in contest_list:
            contest_name = contest_info["name"]
            contest_date = contest_info["date"]
            contest_link = contest_info["link"]

            self.log(
                "info",
                f"Start processing contest: {contest_name} ({contest_date})",
            )

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

            self.log(
                "info",
                f"Finished processing contest: {contest_name} ({contest_date})",
            )

    def fetch_submissions_fetch_source_code(self, entry):
        raise NotImplementedError

    def fetch_submissions_get_submissions(self):
        raise NotImplementedError

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
                code = self.fetch_submissions_fetch_source_code(entry)

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

    def _register_submission(self, submission_entry):
        """
        Register a submission entry. This method is called after fetching each submission.
        Return a boolean indicating whether to stop fetching submissions.
        """
        submit_time = datetime.fromisoformat(submission_entry["submit_time"])
        submission_id = submission_entry["submission_id"]

        # if submit_time < self.last_update_time:
        #     self.log(
        #         "info",
        #         f"Reached last update (Submission {submission_id}), stopping.",
        #     )
        #     return True

        self._update_submission_status(submission_entry)
        return False

    def fetch_submissions(self):
        # Load last update time and staged submissions
        self.last_update = self._load_file(self.last_update_path, default={})
        last_update_time_str = self.last_update.get("qoj", "1970-01-01T00:00:00")
        self.last_update_time = datetime.fromisoformat(last_update_time_str)

        self.contests = self._load_file(self.contests_path)
        self.staged_submissions = self._load_file(self.submissions_path)

        # First try updating existing staged submissions
        new_staged = []
        for entry in self.staged_submissions:
            if not self._update_submission_status(entry):
                new_staged.append(entry)
        self.staged_submissions = new_staged
        self._write_file(self.submissions_path, self.staged_submissions)

        # Fetch new submissions
        self.fetch_submissions_get_submissions()

        self.last_update[self.platform_name] = datetime.now().isoformat()
        self._write_file(self.last_update_path, self.last_update)
