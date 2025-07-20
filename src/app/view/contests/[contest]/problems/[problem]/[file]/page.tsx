import fs from "fs";
import path from "path";
import FileViewer from "@/components/file-viewer/file-viewer";
import { FiDownload, FiFileText } from "react-icons/fi";

import getFileMetadata from "@/utils/get-file-metadata";
import MetaDataDisplay from "@/components/metadata-display";
import { PREFIX_URL } from "@/lib/global";

export async function generateStaticParams() {
  const contestsDir = path.join(process.cwd(), "contests");
  const contests = fs.readdirSync(contestsDir);

  const params = [];
  for (const contest of contests) {
    const problemsDir = path.join(contestsDir, contest, "problems");
    if (!fs.existsSync(problemsDir)) continue;
    const problems = fs.readdirSync(problemsDir);
    for (const problem of problems) {
      const problemPath = path.join(problemsDir, problem);
      const files = fs.readdirSync(problemPath);
      for (const file of files) {
        params.push({
          contest,
          problem,
          file,
        });
      }
    }
  }
  return params;
}

export default async function FilePage(props: {
  params: Promise<{ contest: string; problem: string; file: string }>;
}) {
  const params = await props.params;
  const contest = decodeURIComponent(params.contest);
  const problem = decodeURIComponent(params.problem);
  const file = decodeURIComponent(params.file);

  const rawFilePath = path.join(PREFIX_URL, "contests", contest, "problems", problem, file);

  const contestMetadata = getFileMetadata(
    path.join(process.cwd(), "contests", contest),
    path.join(process.cwd(), "contests", contest, "contest.json"),
  );

  const problemMetadata = getFileMetadata(
    path.join(process.cwd(), "contests", contest, "problems", problem),
    path.join(process.cwd(), "contests", contest, "problems", problem, "problem.json"),
  );

  const fileMetadata = getFileMetadata(
    path.join(process.cwd(), "contests", contest, "problems", problem, file),
    path.join(process.cwd(), "contests", contest, "problems", problem, file + ".json"),
  );

  return (
    <div className="flex min-h-screen justify-center py-4">
      <div className="mx-auto w-4/5">
        <header className="relative w-full rounded-lg py-2 text-slate-300">
          <h1 className="text-2xl font-semibold tracking-wide">File Viewer</h1>
          <p className="ml-4 mt-2 text-base text-gray-400">
            <span className="px-2 text-lg text-gray-200">/</span>
            {contest}
            <span className="px-2 text-lg text-slate-300">/</span>
            {problem}
            <span className="px-2 text-lg text-slate-300">/</span>
            {file}
          </p>
          <div className="absolute right-8 top-2 flex items-center gap-2">
            <a
              href={rawFilePath}
              download
              className="rounded bg-gray-700 px-3 py-1 text-sm text-white hover:bg-gray-600"
            >
              <FiDownload className="mr-2 inline-block text-base" />
              Download
            </a>
            <a
              href={rawFilePath}
              target="_blank"
              rel="noopener noreferrer"
              className="rounded bg-gray-700 px-3 py-1 text-sm text-white hover:bg-gray-600"
            >
              <FiFileText className="mr-2 inline-block text-base" />
              Raw File
            </a>
          </div>
        </header>
        <main className="mt-4 flex w-full items-center justify-center">
          <main className="flex w-full items-start justify-center gap-4">
            <div className="flex-grow">
              <FileViewer
                dirPath={path.join("contests", contest, "problems", problem)}
                fileName={file}
              />
            </div>
            <div className="flex-shrink-0 basis-1/5 space-y-2">
              <MetaDataDisplay name={"File"} metadata={fileMetadata} />
              <MetaDataDisplay name={"Problem"} metadata={problemMetadata} />
              <MetaDataDisplay name={"Contest"} metadata={contestMetadata} />
            </div>
          </main>
        </main>
      </div>
    </div>
  );
}
