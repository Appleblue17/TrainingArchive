import fs from "fs";
import path from "path";
import FileViewerPDFWrapper from "./file-viewer-pdf-wrapper";
import FileViewerSource from "./file-viewer-source";
import FileViewerMarkdownWrapper from "./file-viewer-markdown-wrapper";

import { BASE_URL, allowedExtensions } from "@/lib/global";
import { FiDownload, FiFileText } from "react-icons/fi";

export default function FileViewer({ dirPath, fileName }: { dirPath: string; fileName: string }) {
  const filePath = path.join(process.cwd(), dirPath, fileName);
  const ext = path.extname(fileName).toLowerCase();

  if (fs.existsSync(filePath)) {
    if (allowedExtensions.includes(ext)) {
      if (ext === ".pdf") {
        // For PDF files, use the PDF viewer component
        const pdfPath = path.join(BASE_URL, dirPath, fileName);
        return <FileViewerPDFWrapper pdfPath={pdfPath} />;
      }
      if (ext === ".md") {
        // For Markdown files, use remark to convert to HTML
        const dirPathURL = path.join(BASE_URL, dirPath);
        return (
          <FileViewerMarkdownWrapper
            dirPath={dirPathURL}
            raw={fs.readFileSync(filePath, "utf-8")}
          />
        );
      } else {
        // Source code or other file types can be handled here
        return <FileViewerSource code={fs.readFileSync(filePath, "utf-8")} ext={ext} />;
      }
    } else {
      // If the file is not a text file, show a message and allow download
      const downloadPath = path.join(BASE_URL, dirPath, fileName);
      return (
        <div className="relative flex h-[85dvh] w-full min-w-0 max-w-full items-center justify-center rounded border-2 border-gray-600 bg-zinc-800">
          <div className="flex flex-col items-center">
            <p className="text-xl text-gray-400">This file type is not supported for viewing.</p>

            <div className="mt-4 flex items-center justify-center gap-4">
              <a
                href={downloadPath}
                download
                className="rounded bg-gray-700 px-3 py-1 text-base text-white hover:bg-gray-600"
              >
                <FiDownload className="mr-2 inline-block text-base" />
                Download
              </a>

              <a
                href={downloadPath}
                target="_blank"
                rel="noopener noreferrer"
                className="rounded bg-gray-700 px-3 py-1 text-base text-white hover:bg-gray-600"
              >
                <FiFileText className="mr-2 inline-block text-base" />
                Raw File
              </a>
            </div>
          </div>
        </div>
      );
    }
  } else
    return (
      <div className="flex h-full items-center justify-center">
        <p className="text-red-500">File not found: {filePath}</p>
      </div>
    );
}
