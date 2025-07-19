import fs from "fs";
import path from "path";
import FileViewerPDFWrapper from "./file-viewer-pdf-wrapper";
import FileViewerSource from "./file-viewer-source";
import FileViewerMarkdownWrapper from "./file-viewer-markdown-wrapper";

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
      // For PDF files, use the PDF viewer component
      const pdfPath = path.join("/contests", contest, "problems", problem, file);
      return <FileViewerPDFWrapper pdfPath={pdfPath} />;
    }
    if (ext === ".md") {
      // For Markdown files, use remark to convert to HTML
      const dirPath = path.join("http://localhost:3000/", "contests", contest, "problems", problem);
      return (
        <FileViewerMarkdownWrapper dirPath={dirPath} raw={fs.readFileSync(filePath, "utf-8")} />
      );
    } else {
      // Source code or other file types can be handled here
      return <FileViewerSource code={fs.readFileSync(filePath, "utf-8")} ext={ext} />;
    }
  } else
    return (
      <div className="flex h-full items-center justify-center">
        <p className="text-red-500">File not found: {filePath}</p>
      </div>
    );
}
