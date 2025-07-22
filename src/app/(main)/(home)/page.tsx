import fs from "fs";
import path from "path";
import ContestTable from "./contest-table";

import { ProblemInfoType, ContestInfoType } from "@/lib/types";
import getFileMetadata from "@/utils/get-file-metadata";
import { allowedExtensions } from "@/lib/global";

function getFilesInfo(directory: string) {
  const files = fs.readdirSync(directory);
  // only show files with allowed extensions and not .json
  return files
    .filter((file) => {
      const fullPath = path.join(directory, file);
      const ext = path.extname(file).toLowerCase();
      return fs.statSync(fullPath).isFile() && allowedExtensions.includes(ext) && ext !== ".json";
    })
    .map((file) => {
      return getFileMetadata(path.join(directory, file), path.join(directory, file + ".json"));
    })
    .filter((file) => file !== null);
}

function getProblemInfo(problemPath: string, relProblemPath: string): ProblemInfoType {
  const problemInfo: ProblemInfoType = {
    rel_path: relProblemPath,
    files: getFilesInfo(problemPath),
  };

  if (fs.existsSync(problemPath)) {
    const jsonPath = path.join(problemPath, "problem.json");
    if (fs.existsSync(jsonPath)) {
      const content = fs.readFileSync(jsonPath, "utf-8");
      const json = JSON.parse(content);
      Object.assign(problemInfo, json);
    }
  }
  return problemInfo;
}

function getContests(): ContestInfoType[] {
  const contestsDir = path.join(process.cwd(), "contests");
  const contestFolders = fs.readdirSync(contestsDir);

  const contests: ContestInfoType[] = [];
  for (const contest of contestFolders) {
    const contestPath = path.join(contestsDir, contest);

    const contestInfo: ContestInfoType = {
      rel_path: path.join("contests", contest),
      date: "??-??-????",
      name: "???",
      platform: "unknown",
      problems: [],
      files: getFilesInfo(contestPath),
    };

    const jsonPath = path.join(contestPath, "contest.json");
    if (fs.existsSync(jsonPath)) {
      const content = fs.readFileSync(jsonPath, "utf-8");
      const json = JSON.parse(content);
      Object.assign(contestInfo, json);
    }

    const problemsPath = path.join(contestPath, "problems");
    if (fs.existsSync(problemsPath)) {
      const problemFolders = fs.readdirSync(problemsPath);
      for (const folder of problemFolders) {
        const problemInfo = getProblemInfo(
          path.join(problemsPath, folder),
          path.join("contests", contest, "problems", folder),
        );
        contestInfo.problems.push(problemInfo);
      }
    }
    contests.push(contestInfo);
  }
  return contests;
}

export default function HomePage() {
  const contests = getContests();

  return <ContestTable contests={contests} />;
}
