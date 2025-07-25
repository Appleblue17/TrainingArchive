"use client";
import React, { useEffect, useState } from "react";
import path from "path";
import clsx from "clsx";
import { FiCheck, FiChevronRight, FiFileText, FiX } from "react-icons/fi";
import { ProblemInfoType, ContestInfoType, FileMetadataType, CodeFileType } from "@/lib/types";
import MetaDataDisplay, { formatDate } from "@/components/metadata-display";
import { PREFIX_URL } from "@/lib/global";

// Helper: Convert seconds to HH:MM:SS
function convertDurationToHHMMSS(duration: number): string {
  const hours = Math.floor(duration / 3600);
  const minutes = Math.floor((duration % 3600) / 60);
  const seconds = duration % 60;
  return `${hours.toString().padStart(2, "0")}:${minutes
    .toString()
    .padStart(2, "0")}:${seconds.toString().padStart(2, "0")}`;
}

// Helper: Check if solved in contest
function isSolvedInContest(
  submitTime: string | Date | null,
  contestEndTime: string | Date | null,
): boolean {
  if (!submitTime || !contestEndTime) return false;
  const submitDate = new Date(submitTime);
  const endDate = new Date(contestEndTime);
  return submitDate <= endDate;
}

// Helper: Get display time for submissions
function getInContestTime(
  submitTime: string | Date | null,
  contestEndTime: string | Date | null,
): string {
  if (submitTime && contestEndTime) {
    const submitDate = new Date(submitTime);
    const endDate = new Date(contestEndTime);
    const timeDiff = endDate.getTime() - submitDate.getTime();
    if (timeDiff > 0) return convertDurationToHHMMSS(timeDiff / 1000);
  }
  return formatDate(submitTime);
}

// File list component
function FileList({ files, relPath }: { files: FileMetadataType[]; relPath: string }) {
  return (
    <div className="ml-6 flex items-center justify-start gap-6 rounded border border-gray-500 bg-gray-800 px-4 py-2">
      {files.map((file, idx) => (
        <div key={idx} className="flex items-center justify-between">
          <a
            href={path.join(PREFIX_URL, "view", relPath, file.name!)}
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
  );
}

// Problem row component
function ProblemRow({
  problem,
  idx,
  contestEndTime,
  problemLetter,
  setSelectedProblemIdx,
  setSelectedFileIdx,
}: {
  problem: ProblemInfoType;
  idx: number;
  contestEndTime: string | Date | null;
  problemLetter: string;
  setSelectedProblemIdx: (idx: number | null) => void;
  setSelectedFileIdx: (idx: number | null) => void;
}) {
  // Find code file for status display
  const codeFile: CodeFileType | undefined = problem.files.find((f) =>
    f.name!.startsWith("code"),
  ) as CodeFileType | undefined;

  // Status/time display
  let statusBlock = null;
  if (codeFile) {
    const isInContest = isSolvedInContest(
      codeFile.submit_time || codeFile.modified_time || null,
      contestEndTime || null,
    );
    const displayTime = getInContestTime(
      codeFile.submit_time || codeFile.modified_time || null,
      contestEndTime || null,
    );
    const submitStatus: string = codeFile.status || "UKN";
    statusBlock = (
      <div className="flex items-center justify-start gap-4 font-mono text-base">
        <span
          className={clsx({
            "text-gray-300": !isInContest,
            "text-yellow-100/80": isInContest,
          })}
        >
          {displayTime}
        </span>
        <span>
          <span className="inline-block min-w-10 text-right align-middle">{codeFile.size}</span>
          <span className="ml-1 text-gray-400">B</span>
        </span>
        <a
          href={path.join(PREFIX_URL, "view", problem.rel_path, codeFile.name!)}
          target="_blank"
          rel="noopener noreferrer"
          className="ml-2 text-gray-100 transition-colors hover:text-blue-300"
        >
          <FiFileText className="inline-block size-5" />
        </a>
        <div className="flex justify-end">
          {submitStatus === "AC" ? (
            <FiCheck className="inline-block size-5 text-green-400" />
          ) : (
            <FiX
              className={clsx("inline-block size-5 text-gray-400/80", {
                "text-red-400/80": submitStatus === "WA",
                "text-purple-400/80": submitStatus === "RE",
                "text-yellow-400/80": submitStatus === "TLE" || submitStatus === "TL",
              })}
            />
          )}
          <span className="ml-1 inline-block min-w-8 text-gray-400">{codeFile.status}</span>
        </div>
      </div>
    );
  }

  return (
    <div
      key={idx}
      onMouseEnter={() => setSelectedProblemIdx(idx)}
      onMouseLeave={() => setSelectedProblemIdx(null)}
      className="flex items-center justify-between pl-6 hover:bg-gray-700/40"
    >
      {/* Problem name and files */}
      <div className="flex items-center justify-start">
        {problem.solved ? (
          <FiCheck className="inline-block size-4 text-green-400" />
        ) : (
          <FiChevronRight className="inline-block size-4 text-gray-200" />
        )}

        <a
          href={problem.link || ""}
          target="_blank"
          rel="noopener noreferrer"
          onClick={(e) => e.stopPropagation()}
          className="ml-3 mr-8 text-base text-gray-100 transition-colors hover:text-blue-300"
        >
          {problemLetter}. {problem.name || `Problem ${idx + 1}`}
        </a>

        {/* Problem files */}
        {problem.files.map((file, fileIdx) => (
          <div
            key={fileIdx}
            onMouseEnter={() => setSelectedFileIdx(fileIdx)}
            onMouseLeave={() => setSelectedFileIdx(null)}
            className="flex items-center justify-between"
          >
            <a
              href={path.join(PREFIX_URL, "view", problem.rel_path, file.name!)}
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
      {statusBlock}
    </div>
  );
}

// Expand block for contest details
function ContestExpandBlock({
  contest,
  showExpandedContent,
  problemLetters,
  setSelectedProblemIdx,
  setSelectedFileIdx,
  displayMetadataName,
  displayMetadata,
  displayMetadataBanner,
}: {
  contest: ContestInfoType;
  showExpandedContent: boolean;
  problemLetters: string[];
  setSelectedProblemIdx: (idx: number | null) => void;
  setSelectedFileIdx: (idx: number | null) => void;
  displayMetadataName: string | null;
  displayMetadata: FileMetadataType | ProblemInfoType | ContestInfoType | null;
  displayMetadataBanner: string[];
}) {
  return (
    <tr>
      <td colSpan={18} className={"border-b border-gray-700 p-0"}>
        <div
          className={"overflow-auto bg-neutral-900 transition-all duration-500 ease-out"}
          style={{
            height: showExpandedContent ? "540px" : "0px",
            opacity: showExpandedContent ? 1 : 0,
          }}
        >
          <div className="my-2 flex h-full w-full">
            <div className="mt-1 flex flex-grow flex-col gap-3">
              {/* Contest files */}
              <FileList files={contest.files} relPath={contest.rel_path} />
              {/* Problems list */}
              <div className="flex flex-col">
                {contest.problems.map((problem, pIdx) => (
                  <ProblemRow
                    key={pIdx}
                    problem={problem}
                    idx={pIdx}
                    contestEndTime={contest.end_time || null}
                    problemLetter={problemLetters[pIdx]}
                    setSelectedProblemIdx={setSelectedProblemIdx}
                    setSelectedFileIdx={setSelectedFileIdx}
                  />
                ))}
                {contest.problems.length === 0 && (
                  <div className="text-center text-base text-gray-300">No problems available</div>
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
        </div>
      </td>
    </tr>
  );
}

// Contest row component
function ContestRow({
  contest,
  idx,
  expandedRow,
  setExpandedRow,
  showExpandedContent,
  setShowExpandedContent,
  problemLetters,
  setSelectedProblemIdx,
  setSelectedFileIdx,
  displayMetadataName,
  displayMetadata,
  displayMetadataBanner,
}: {
  contest: ContestInfoType;
  idx: number;
  expandedRow: number | null;
  setExpandedRow: (idx: number | null) => void;
  showExpandedContent: boolean;
  setShowExpandedContent: (show: boolean) => void;
  problemLetters: string[];
  setSelectedProblemIdx: (idx: number | null) => void;
  setSelectedFileIdx: (idx: number | null) => void;
  displayMetadataName: string | null;
  displayMetadata: FileMetadataType | ProblemInfoType | ContestInfoType | null;
  displayMetadataBanner: string[];
}) {
  const handleRowClick = () => {
    if (expandedRow === idx) {
      setShowExpandedContent(false);
      // Wait for 500ms before collapsing
      setTimeout(() => {
        setExpandedRow(null);
      }, 500);
    } else if (expandedRow === null) {
      setExpandedRow(idx);
      setTimeout(() => {
        setShowExpandedContent(true);
      }, 10);
    } else {
      // no animation
      setExpandedRow(idx);
    }
  };

  return (
    <React.Fragment>
      <tr
        className="cursor-pointer border-b border-gray-700 bg-zinc-800/80 hover:bg-gray-700/40"
        onClick={handleRowClick}
      >
        <td className="border-r border-gray-600 px-2 py-2 text-center text-gray-100">
          {contest.date}
        </td>
        <td className="border-r border-gray-600 px-2 py-2 text-center">
          <a
            href={contest.link || ""}
            target="_blank"
            rel="noopener noreferrer"
            title={contest.name}
            onClick={(e) => e.stopPropagation()}
            className="break-keep text-gray-100 transition-colors hover:text-blue-300"
          >
            {contest.name}
          </a>
        </td>
        {problemLetters.map((letter: string, pIdx: number) => {
          if (pIdx < contest.problems.length) {
            const solvedInContest = isSolvedInContest(
              contest.problems[pIdx].solve_time || null,
              contest.end_time || null,
            );
            return (
              <td
                key={letter}
                className={clsx("relative border-r border-gray-700 text-center text-base", {
                  "bg-green-400/40": contest.problems[pIdx].solved && solvedInContest,
                  "bg-emerald-400/30": contest.problems[pIdx].solved && !solvedInContest,
                })}
              >
                <a
                  href={contest.problems[pIdx].link || ""}
                  target="_blank"
                  rel="noopener noreferrer"
                  onClick={(e) => e.stopPropagation()}
                  className={clsx("text-gray-100 transition-colors hover:text-blue-300", {
                    "text-white": contest.problems[pIdx].solved,
                  })}
                >
                  {letter}
                </a>
                {contest.problems[pIdx].solved && (
                  <FiCheck className="absolute bottom-0 right-0 size-4" />
                )}
              </td>
            );
          } else {
            return (
              <td
                key={letter}
                className={clsx("border-r border-gray-700 text-center text-base", {
                  "border-dashed bg-slate-800/30": pIdx > 13,
                })}
              />
            );
          }
        })}
      </tr>
      {/* Expanded block for contest details */}
      {expandedRow === idx && (
        <ContestExpandBlock
          contest={contest}
          showExpandedContent={showExpandedContent}
          problemLetters={problemLetters}
          setSelectedProblemIdx={setSelectedProblemIdx}
          setSelectedFileIdx={setSelectedFileIdx}
          displayMetadataName={displayMetadataName}
          displayMetadata={displayMetadata}
          displayMetadataBanner={displayMetadataBanner}
        />
      )}
    </React.Fragment>
  );
}

// Main contest table component
export default function ContestTable({ contests }: { contests: ContestInfoType[] }) {
  const [expandedRow, setExpandedRow] = useState<number | null>(null);
  const [showExpandedContent, setShowExpandedContent] = useState<boolean>(false);

  const [selectedProblemIdx, setSelectedProblemIdx] = useState<number | null>(null);
  const [selectedFileIdx, setSelectedFileIdx] = useState<number | null>(null);

  const [displayMetadataName, setDisplayMetadataName] = useState<string | null>(null);
  const [displayMetadata, setDisplayMetadata] = useState<
    FileMetadataType | ProblemInfoType | ContestInfoType | null
  >(null);
  const [displayMetadataBanner, setDisplayMetadataBanner] = useState<string[]>([]);

  useEffect(() => {
    if (selectedFileIdx !== null && expandedRow !== null && selectedProblemIdx !== null) {
      // Show file metadata
      const contest = contests[expandedRow];
      const problem = contest.problems[selectedProblemIdx];
      const file = problem.files[selectedFileIdx];
      setDisplayMetadataName("File");
      setDisplayMetadata(file);
      setDisplayMetadataBanner(["link"]);
    } else if (selectedProblemIdx !== null && expandedRow !== null) {
      // Show problem metadata
      const contest = contests[expandedRow];
      const problemInfo = contest.problems[selectedProblemIdx];
      setDisplayMetadataName("Problem");
      setDisplayMetadata(problemInfo);
      setDisplayMetadataBanner(["rel_path", "files", "link"]);
    } else if (expandedRow !== null) {
      // Show contest metadata
      const contestInfo = contests[expandedRow];
      setDisplayMetadataName("Contest");
      setDisplayMetadata(contestInfo);
      setDisplayMetadataBanner(["rel_path", "problems", "files", "link"]);
    }
  }, [expandedRow, selectedProblemIdx, selectedFileIdx, contests]);

  const problemLetters = Array.from({ length: 17 }, (_, i) => String.fromCharCode(65 + i));

  return (
    <table className="w-[calc(100%+144px)] table-fixed border-2 border-gray-600 text-sm">
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
          <ContestRow
            key={idx}
            contest={contest}
            idx={idx}
            expandedRow={expandedRow}
            setExpandedRow={setExpandedRow}
            showExpandedContent={showExpandedContent}
            setShowExpandedContent={setShowExpandedContent}
            problemLetters={problemLetters}
            setSelectedProblemIdx={setSelectedProblemIdx}
            setSelectedFileIdx={setSelectedFileIdx}
            displayMetadataName={displayMetadataName}
            displayMetadata={displayMetadata}
            displayMetadataBanner={displayMetadataBanner}
          />
        ))}
      </tbody>
    </table>
  );
}
