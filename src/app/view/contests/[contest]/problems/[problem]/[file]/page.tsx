import fs from "fs";
import path from "path";
import FileViewer from "./file-viewer";
import { FiDownload, FiFileText } from "react-icons/fi";

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

async function getFileMetadata(filePath: string, metadataPath: string) {
  const stats = await fs.promises.stat(filePath);

  const metadata: { [key: string]: any } = {
    name: path.basename(filePath),
    modified_time: stats.mtime,
  };
  if (stats.isFile()) {
    metadata.size = stats.size; // Size in bytes
  }

  // Check if metadata file exists
  if (fs.existsSync(metadataPath)) {
    const metadataContent = JSON.parse(fs.readFileSync(metadataPath, "utf-8"));
    Object.assign(metadata, metadataContent);
  }
  return metadata;
}

export default async function FilePage(props: {
  params:
    | { contest: string; problem: string; file: string }
    | Promise<{ contest: string; problem: string; file: string }>;
}) {
  const params = await props.params;
  const contest = decodeURIComponent(params.contest);
  const problem = decodeURIComponent(params.problem);
  const file = decodeURIComponent(params.file);

  const rawFilePath = "/" + path.join("contests", contest, "problems", problem, file);

  const contestMetadata = await getFileMetadata(
    path.join(process.cwd(), "contests", contest),
    path.join(process.cwd(), "contests", contest, "contest.json"),
  );

  const problemMetadata = await getFileMetadata(
    path.join(process.cwd(), "contests", contest, "problems", problem),
    path.join(process.cwd(), "contests", contest, "problems", problem, "problem.json"),
  );

  const fileMetadata = await getFileMetadata(
    path.join(process.cwd(), "contests", contest, "problems", problem, file),
    path.join(process.cwd(), "contests", contest, "problems", problem, file + ".json"),
  );

  console.log(rawFilePath);

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
              <FileViewer contest={contest} problem={problem} file={file} />
            </div>
            <div className="flex-shrink-0 basis-1/5">
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

function MetaDataDisplay({ name, metadata }: { name: string; metadata: { [key: string]: any } }) {
  if (!metadata) return null;

  // Helper function: format key name
  function formatKey(key: string) {
    return key.replace(/_/g, " ").replace(/\b\w/g, (c) => c.toUpperCase());
  }

  // Helper function: format bytes
  function formatSize(size: number) {
    if (size < 1024) return `${size} B`;
    if (size < 1024 * 1024) return `${(size / 1024).toFixed(1)} KB`;
    return `${(size / 1024 / 1024).toFixed(2)} MB`;
  }
  // Helper function: format date
  function formatDate(val: any) {
    const d = typeof val === "string" ? new Date(val) : val;
    if (d instanceof Date && !isNaN(d.getTime())) {
      return d
        .toLocaleString("zh-CN", {
          year: "numeric",
          month: "2-digit",
          day: "2-digit",
          hour: "2-digit",
          minute: "2-digit",
          second: "2-digit",
          hour12: false,
        })
        .replace(/-/g, "/");
    }
    return String(val);
  }
  return (
    <div className="my-2 overflow-auto">
      <h2 className="px-1 py-1 text-sm font-medium text-gray-300">{name}</h2>
      <div className="rounded border-2 border-gray-400 bg-black/80 p-3 font-mono text-sm text-green-300">
        {Object.entries(metadata).map(([key, value]) => {
          const keyDisplay = <span className="text-blue-400">[{formatKey(key)}]</span>;
          let valueDisplay;
          if (key === "size" && typeof value === "number") {
            valueDisplay = <span className="text-yellow-400">{formatSize(value)}</span>;
          } else if (key.includes("time_limit") && typeof value === "number") {
            // unit: seconds
            valueDisplay = <span className="text-yellow-400">{value} s</span>;
          } else if (key.includes("memory_limit") && typeof value === "number") {
            // unit: kilobytes
            valueDisplay = <span className="text-yellow-400">{value} MB</span>;
          } else if (key.includes("time") && value) {
            valueDisplay = <span className="text-pink-400">{formatDate(value)}</span>;
          } else if (key.includes("link") && typeof value === "string") {
            valueDisplay = (
              <a
                href={value}
                target="_blank"
                rel="noopener noreferrer"
                className="text-indigo-400 underline hover:text-indigo-200"
              >
                {value}
              </a>
            );
          } else if (typeof value === "number") {
            valueDisplay = <span className="text-yellow-300">{value}</span>;
          } else if (typeof value === "boolean") {
            valueDisplay = <span className="text-cyan-400">{value ? "true" : "false"}</span>;
          } else if (typeof value === "object" && value !== null) {
            valueDisplay = <span className="text-gray-400">{JSON.stringify(value)}</span>;
          } else {
            valueDisplay = <span className="text-green-200">{String(value)}</span>;
          }
          return (
            <div
              key={key}
              className="mb-1 break-all"
              style={{ textIndent: "-1.2em", paddingLeft: "1.2em" }}
            >
              {keyDisplay} {valueDisplay}
            </div>
          );
        })}
      </div>
    </div>
  );
}
