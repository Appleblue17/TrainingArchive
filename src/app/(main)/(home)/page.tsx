import fs from "fs";
import Link from "next/link";
import path from "path";
import clsx from "clsx";

import { FiCheck } from "react-icons/fi";

type ProblemInfoType = {
  rel_path: string;
  link?: string;
  files: string[];
  [key: string]: any; // Allow additional properties
};

type ContestInfoType = {
  rel_path: string;
  link?: string;
  date: string;
  title: string;
  duration: string;
  platform: string;
  problems: ProblemInfoType[];
  files: string[];
  [key: string]: any; // Allow additional properties
};

function getFilesInfo(directory: string): string[] {
  const files = fs.readdirSync(directory);
  // Search for every file that does not end with .json
  return files
    .filter((file) => fs.statSync(path.join(directory, file)).isFile())
    .filter((file) => !file.endsWith(".json"));
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

      // Copy every property from the JSON to problemInfo
      Object.assign(problemInfo, json);
    }
  }
  return problemInfo;
}

async function getContests(): Promise<ContestInfoType[]> {
  const contestsDir = path.join(process.cwd(), "contests");
  const contestFolders = fs.readdirSync(contestsDir);

  return contestFolders.map((contest) => {
    const contestPath = path.join(contestsDir, contest);

    const contestInfo: ContestInfoType = {
      rel_path: path.join("contests", contest),
      date: "??-??-????",
      title: "???",
      duration: "??:??:?? - ??:??:??",
      platform: "unknown",
      problems: [],
      files: getFilesInfo(contestPath),
    };

    const jsonPath = path.join(contestPath, "contest.json");
    if (fs.existsSync(jsonPath)) {
      const content = fs.readFileSync(jsonPath, "utf-8");
      const json = JSON.parse(content);

      // Copy every property from the JSON to contestInfo
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
    return contestInfo;
  });
}

export default async function HomePage() {
  const contests = await getContests();
  console.log("Contests:", contests);
  console.log(
    "Contests:",
    contests.flatMap((c) => c.problems),
  );

  const problemLetters = Array.from({ length: 16 }, (_, i) => String.fromCharCode(65 + i));

  return (
    <table className="table-fixed border-2 border-gray-600 text-sm" style={{ width: "calc(100%)" }}>
      <thead>
        <tr className="border-b-2 border-gray-500">
          <th className="w-32 whitespace-nowrap border-r border-gray-600 bg-gray-800 px-2 py-2 text-center text-gray-200">
            Date
          </th>
          <th className="w-auto border-r border-gray-600 bg-gray-800 px-2 py-2 text-center text-gray-200">
            Title
          </th>
          {problemLetters.map((letter) => (
            <th
              key={letter}
              className="w-12 border-r border-gray-700 bg-gray-800 text-center text-base text-gray-200"
            >
              {letter}
            </th>
          ))}
        </tr>
      </thead>
      <tbody>
        {contests.map((contest, idx) => (
          <tr key={idx} className="border-b border-gray-700">
            <td className="border-r border-gray-600 px-2 py-2 text-center text-gray-100">
              {contest.date}
            </td>
            <td className="border-r border-gray-600 px-2 py-2 text-center">
              <Link
                href={contest.link || ""}
                className="text-gray-100 transition-colors hover:text-blue-300"
              >
                {contest.title}
              </Link>
            </td>

            {problemLetters.map((letter, idx) => {
              if (idx < contest.problems.length) {
                return (
                  <td
                    key={letter}
                    className={clsx("relative border-r border-gray-700 text-center text-base", {
                      "bg-green-400/40":
                        contest.problems[idx].solved && contest.problems[idx].solved_in_contest,
                      "bg-emerald-400/30":
                        contest.problems[idx].solved && !contest.problems[idx].solved_in_contest,
                    })}
                  >
                    <Link
                      href={contest.problems[idx].link || ""}
                      className={clsx("text-gray-100 transition-colors hover:text-blue-300", {
                        "text-white": contest.problems[idx].solved,
                      })}
                    >
                      {letter}
                    </Link>
                    <FiCheck
                      className={clsx("absolute bottom-0 right-0 size-4", {
                        hidden: !contest.problems[idx].solved,
                      })}
                    />
                  </td>
                );
              } else {
                return (
                  <td key={letter} className="border-r border-gray-700 text-center text-base" />
                );
              }
            })}
          </tr>
        ))}
      </tbody>
    </table>
  );
}
