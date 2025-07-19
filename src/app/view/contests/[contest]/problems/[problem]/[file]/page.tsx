import fs from "fs";
import path from "path";
import FileViewer from "./file-viewer";

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
  params:
    | { contest: string; problem: string; file: string }
    | Promise<{ contest: string; problem: string; file: string }>;
}) {
  const params = await props.params;
  const contest = decodeURIComponent(params.contest);
  const problem = decodeURIComponent(params.problem);
  const file = decodeURIComponent(params.file);

  return (
    <div className="flex min-h-screen justify-center py-4">
      <div className="mx-auto w-4/5">
        <header className="w-full rounded-lg py-2 text-slate-300">
          <h1 className="text-2xl font-semibold tracking-wide">File Viewer</h1>
          <p className="ml-4 mt-2 text-base text-gray-400">
            <span className="px-2 text-lg text-gray-200">/</span>
            {contest}
            <span className="px-2 text-lg text-slate-300">/</span>
            {problem}
            <span className="px-2 text-lg text-slate-300">/</span>
            {file}
          </p>
        </header>
        <main className="mt-4 flex w-full items-center justify-center">
          <main className="flex w-full items-start justify-center gap-4">
            <div className="flex-grow">
              <FileViewer contest={contest} problem={problem} file={file} />
            </div>
            <div className="flex-shrink-0 basis-1/5 border-2">
              {/* Sidebar or additional content can go here */}
            </div>
          </main>
        </main>
      </div>
    </div>
  );
}
