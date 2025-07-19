import fs from "fs";
import path from "path";
import FileViewerPDFWrapper from "./file-viewer-pdf-wrapper";

export default function FileViewer({
  contest,
  problem,
  file,
}: {
  contest: string;
  problem: string;
  file: string;
}) {
  const filePath = path.join(process.cwd(), "contests", contest, "problems", problem, file);
  const ext = path.extname(file).toLowerCase();

  if (fs.existsSync(filePath)) {
    if (ext === ".pdf") {
      const pdfPath = path.join("/contests", contest, "problems", problem, file);

      return <FileViewerPDFWrapper pdfPath={pdfPath} />;
    }
  } else
    return (
      <div className="flex h-full items-center justify-center">
        <p className="text-red-500">File not found: {filePath}</p>
      </div>
    );
}
