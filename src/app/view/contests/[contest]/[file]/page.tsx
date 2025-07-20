import fs from "fs";
import path from "path";
import FileViewer from "@/components/file-viewer/file-viewer";
import { FiDownload, FiFileText } from "react-icons/fi";

import getFileMetadata from "@/utils/get-file-metadata";
import MetaDataDisplay from "@/components/metadata-display";

export async function generateStaticParams() {
  const contestsDir = path.join(process.cwd(), "contests");
  const contests = fs.readdirSync(contestsDir);

  const params = [];
  for (const contest of contests) {
    const contestDir = path.join(contestsDir, contest);
    if (!fs.existsSync(contestDir)) continue;
    const files = fs.readdirSync(contestDir);
    for (const file of files) {
      params.push({
        contest,
        file,
      });
    }
  }
  return params;
}

export default async function FilePage(props: {
  params: Promise<{ contest: string; file: string }>;
}) {
  const params = await props.params;
  const contest = decodeURIComponent(params.contest);
  const file = decodeURIComponent(params.file);

  const rawFilePath = path.join("/contests", contest, file);

  const contestMetadata = getFileMetadata(
    path.join(process.cwd(), "contests", contest),
    path.join(process.cwd(), "contests", contest, "contest.json"),
  );

  const fileMetadata = getFileMetadata(
    path.join(process.cwd(), "contests", contest, file),
    path.join(process.cwd(), "contests", contest, file + ".json"),
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
              <FileViewer dirPath={path.join("contests", contest)} fileName={file} />
            </div>
            <div className="flex-shrink-0 basis-1/5 space-y-2">
              <MetaDataDisplay name={"File"} metadata={fileMetadata} />
              <MetaDataDisplay name={"Contest"} metadata={contestMetadata} />
            </div>
          </main>
        </main>
      </div>
    </div>
  );
}
