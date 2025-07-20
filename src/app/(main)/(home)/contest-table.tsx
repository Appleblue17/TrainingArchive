"use client";
import React, { useEffect, useState } from "react";
import path from "path";
import clsx from "clsx";

import { FiAlertCircle, FiCheck, FiChevronRight, FiFileText } from "react-icons/fi";
import { ProblemInfoType, ContestInfoType, FileMetadataType } from "../../../lib/types";

import MetaDataDisplay, { formatDate } from "@/components/metadata-display";
import { PREFIX_URL } from "@/lib/global";

export default function ContestTable({ contests }: { contests: ContestInfoType[] }) {
  const [expandedRow, setExpandedRow] = useState<number | null>(null);
  const [selectedProblemIdx, setSelectedProblemIdx] = useState<number | null>(null);
  const [selectedFileIdx, setSelectedFileIdx] = useState<number | null>(null);

  const [displayMetadataName, setDisplayMetadataName] = useState<string | null>(null);
  const [displayMetadata, setDisplayMetadata] = useState<
    FileMetadataType | ProblemInfoType | ContestInfoType | null
  >(null);
  const [displayMetadataBanner, setDisplayMetadataBanner] = useState<string[]>([]);

  useEffect(() => {
    if (selectedFileIdx !== null) {
      // show file
      const contest = contests[expandedRow || 0];
      const problem = contest.problems![selectedProblemIdx || 0];
      const file = problem.files![selectedFileIdx];
      setDisplayMetadataName("File");
      setDisplayMetadata(file);
      setDisplayMetadataBanner(["link"]);
    } else if (selectedProblemIdx !== null) {
      // show problem
      const contest = contests[expandedRow || 0];
      const problemInfo = contest.problems![selectedProblemIdx];
      setDisplayMetadataName("Problem");
      setDisplayMetadata(problemInfo);
      setDisplayMetadataBanner(["rel_path", "files", "link"]);
    } else {
      // show contest
      const contestInfo = contests[expandedRow || 0];
      setDisplayMetadataName("Contest");
      setDisplayMetadata(contestInfo);
      setDisplayMetadataBanner(["rel_path", "problems", "files", "link"]); // Show first file of the contest
    }
  }, [expandedRow, selectedProblemIdx, selectedFileIdx, contests]);

  const problemLetters = Array.from({ length: 16 }, (_, i) => String.fromCharCode(65 + i));

  return (
    <table className="w-full table-fixed border-2 border-gray-600 text-sm">
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
          <React.Fragment key={idx}>
            <tr
              className="cursor-pointer border-b border-gray-700 bg-zinc-800/80 hover:bg-gray-700/40"
              onClick={() => setExpandedRow(expandedRow === idx ? null : idx)}
            >
              <td className="border-r border-gray-600 px-2 py-2 text-center text-gray-100">
                {contest.date}
              </td>
              <td className="border-r border-gray-600 px-2 py-2 text-center">
                <a
                  href={contest.link || ""}
                  target="_blank"
                  rel="noopener noreferrer"
                  onClick={(e) => e.stopPropagation()}
                  className="text-gray-100 transition-colors hover:text-blue-300"
                >
                  {contest.title}
                </a>
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
                      <a
                        href={contest.problems[idx].link || ""}
                        target="_blank"
                        rel="noopener noreferrer"
                        onClick={(e) => e.stopPropagation()}
                        className={clsx("text-gray-100 transition-colors hover:text-blue-300", {
                          "text-white": contest.problems[idx].solved,
                        })}
                      >
                        {letter}
                      </a>
                      {contest.problems[idx].solved && (
                        <FiCheck className="absolute bottom-0 right-0 size-4" />
                      )}
                    </td>
                  );
                } else {
                  return (
                    <td key={letter} className="border-r border-gray-700 text-center text-base" />
                  );
                }
              })}
            </tr>

            {/* Expand Block */}
            <tr>
              <td
                colSpan={18}
                className={clsx("border-gray-700 p-0", {
                  "border-b": expandedRow === idx,
                })}
              >
                <div
                  className={clsx(
                    "overflow-auto bg-neutral-900 transition-all duration-500 ease-in-out",
                    {
                      "py-2": expandedRow === idx,
                    },
                  )}
                  style={{
                    height: expandedRow === idx ? "500px" : "0px",
                  }}
                >
                  {expandedRow === idx && (
                    <div className="flex h-full w-full">
                      <div className="mt-1 flex flex-grow flex-col gap-3">
                        {/* Contest Files */}
                        <div className="ml-6 flex items-center justify-start gap-6 rounded border border-gray-500 bg-gray-800 px-4 py-2">
                          {contest.files.map((file, idx) => (
                            <div key={idx} className="flex items-center justify-between">
                              <a
                                href={path.join(PREFIX_URL, "view", contest.rel_path, file.name!)}
                                target="_blank"
                                rel="noopener noreferrer"
                                className="text-gray-100 transition-colors hover:text-blue-300"
                              >
                                <FiFileText className="inline-block size-4" />
                                <span className="ml-1">{file.name}</span>
                              </a>
                            </div>
                          ))}
                        </div>

                        {/* Problems List */}
                        <div className="flex flex-col">
                          {contest.problems.map((problem, idx) => (
                            <div
                              key={idx}
                              onMouseEnter={() => setSelectedProblemIdx(idx)}
                              onMouseLeave={() => setSelectedProblemIdx(null)}
                              className="flex items-center justify-between px-6 hover:bg-gray-700/40"
                            >
                              {/* Problem name and files */}
                              <div className="flex items-center justify-start">
                                {!problem.solved ? (
                                  <FiChevronRight className="inline-block size-4 text-gray-200" />
                                ) : problem.solved_in_contest ? (
                                  <FiCheck className="inline-block size-4 text-green-400" />
                                ) : (
                                  <FiCheck className="inline-block size-4 text-emerald-400/60" />
                                )}

                                <a
                                  href={contest.problems[idx].link || ""}
                                  target="_blank"
                                  rel="noopener noreferrer"
                                  onClick={(e) => e.stopPropagation()}
                                  className="mx-3 text-base text-gray-100 transition-colors hover:text-blue-300"
                                >
                                  {problemLetters[idx]}. {problem.name || `Problem ${idx + 1}`}
                                </a>

                                {/* Problem files */}
                                {problem.files.map((file, idx) => (
                                  <div
                                    key={idx}
                                    onMouseEnter={() => setSelectedFileIdx(idx)}
                                    onMouseLeave={() => setSelectedFileIdx(null)}
                                    className="flex items-center justify-between"
                                  >
                                    <a
                                      href={path.join(
                                        PREFIX_URL,
                                        "view",
                                        problem.rel_path,
                                        file.name!,
                                      )}
                                      target="_blank"
                                      rel="noopener noreferrer"
                                      className="p-2 text-gray-100 transition-colors hover:text-blue-300"
                                    >
                                      <FiFileText className="inline-block size-4" />
                                      <span className="ml-1">{file.name}</span>
                                    </a>
                                  </div>
                                ))}
                              </div>
                              {/* Submitted file status */}
                              {problem.solved &&
                                (() => {
                                  // Find if "code.*" file exists
                                  const codeFile = problem.files.find((f) =>
                                    f.name!.startsWith("code"),
                                  );
                                  return codeFile ? (
                                    <div className="flex items-center justify-start gap-4">
                                      <span>
                                        {codeFile.modified_time
                                          ? formatDate(codeFile.modified_time)
                                          : "????/??/?? ??:??:??"}
                                      </span>
                                      <span>
                                        <span className="inline-block min-w-8 text-right align-middle">
                                          {typeof codeFile.size === "number"
                                            ? codeFile.size
                                            : "???"}
                                        </span>
                                        <span className="ml-1 text-gray-400">B</span>
                                      </span>
                                      <a
                                        href={path.join(
                                          PREFIX_URL,
                                          "view",
                                          problem.rel_path,
                                          codeFile.name!,
                                        )}
                                        target="_blank"
                                        rel="noopener noreferrer"
                                        className="text-gray-100 transition-colors hover:text-blue-300"
                                      >
                                        <FiFileText className="inline-block size-4" />
                                      </a>
                                    </div>
                                  ) : (
                                    <FiAlertCircle className="inline-block size-4 text-yellow-300/80" />
                                  );
                                })()}
                            </div>
                          ))}
                          {contest.problems.length === 0 && (
                            <div className="text-center text-base text-gray-300">
                              No problems available
                            </div>
                          )}
                        </div>
                      </div>
                      <div className="flex-shrink-0 basis-1/4 px-4">
                        <MetaDataDisplay
                          name={displayMetadataName || undefined}
                          metadata={displayMetadata as FileMetadataType}
                          metadataBanner={displayMetadataBanner}
                        />
                      </div>
                    </div>
                  )}
                </div>
              </td>
            </tr>
          </React.Fragment>
        ))}
      </tbody>
    </table>
  );
}
