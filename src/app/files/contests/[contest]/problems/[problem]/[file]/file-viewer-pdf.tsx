import { useRef, useEffect, useState } from "react";
import { FiMinus, FiPlus } from "react-icons/fi";
import { Document, Page, pdfjs } from "react-pdf";
import "react-pdf/dist/Page/AnnotationLayer.css";
import "react-pdf/dist/Page/TextLayer.css";

export default function FileViewerPDF({ pdfPath }: { pdfPath: string }) {
  useEffect(() => {
    pdfjs.GlobalWorkerOptions.workerSrc = "/pdf.worker.min.mjs";
  }, []);

  const [numPages, setNumPages] = useState<number>();
  const [pageNumber, setPageNumber] = useState<number>(1);
  const [scale, setScale] = useState(1.0);
  const containerRef = useRef<HTMLDivElement>(null);
  const [containerWidth, setContainerWidth] = useState(600);
  const [inputPage, setInputPage] = useState(pageNumber);

  const pageRefs = useRef<(HTMLDivElement | null)[]>([]);

  useEffect(() => {
    setInputPage(pageNumber); // 当 pageNumber 变化时同步 inputPage
  }, [pageNumber]);

  useEffect(() => {
    if (pageRefs.current[pageNumber - 1]) {
      pageRefs.current[pageNumber - 1]?.scrollIntoView({ behavior: "smooth", block: "start" });
    }
  }, [pageNumber]);

  useEffect(() => {
    if (containerRef.current) {
      setContainerWidth(containerRef.current.offsetWidth - 32); // Subtracting padding
    }
  }, []);

  function onDocumentLoadSuccess({ numPages }: { numPages: number }): void {
    setNumPages(numPages);
  }

  return (
    <div className="flex h-[85dvh] w-full flex-col rounded border-2 border-gray-600 bg-zinc-800">
      {/* Header */}
      <div className="flex shrink-0 items-center justify-center py-1">
        <div className="flex items-center gap-1 px-2">
          <button
            onClick={() => setScale((s) => Math.max(0.5, s - 0.1))}
            className="rounded px-2 py-2 text-white hover:bg-zinc-700"
          >
            <FiMinus className="size-4" />
          </button>
          <button
            onClick={() => setScale((s) => Math.min(1, s + 0.1))}
            className="rounded px-2 py-2 text-white hover:bg-zinc-700"
          >
            <FiPlus className="size-4" />
          </button>
        </div>
        <div className="flex items-center gap-1 border-l border-gray-600 px-2">
          <input
            type="number"
            value={inputPage}
            min={1}
            max={numPages || 1}
            onChange={(e) => setInputPage(Number(e.target.value))}
            onBlur={() => {
              if (inputPage >= 1 && inputPage <= (numPages || 1) && inputPage !== pageNumber) {
                setPageNumber(inputPage);
              } else {
                setInputPage(pageNumber); // 恢复为当前页
              }
            }}
            onKeyDown={(e) => {
              if (e.key === "Enter") {
                if (inputPage >= 1 && inputPage <= (numPages || 1) && inputPage !== pageNumber) {
                  setPageNumber(inputPage);
                } else {
                  setInputPage(pageNumber);
                }
              }
            }}
            className="w-16 rounded bg-gray-700 px-2 py-1 text-white"
          />
          <span className="text-gray-200">of {numPages}</span>
        </div>
      </div>

      {/* PDF Content  */}
      <div
        ref={containerRef}
        className="no-scrollbar flex flex-1 items-start justify-center overflow-auto px-4"
      >
        <Document file={pdfPath} onLoadSuccess={onDocumentLoadSuccess}>
          {Array.from({ length: numPages || 0 }, (_, i) => (
            <div
              key={i + 1}
              style={{
                marginBottom: i === numPages! - 1 ? 0 : `${containerWidth * scale * 0.02}px`,
              }}
            >
              <Page
                pageNumber={i + 1}
                width={containerWidth ? Math.floor(containerWidth * scale) : undefined}
              />
            </div>
          ))}
        </Document>
      </div>
      {/* Footer: 页码和翻页按钮 */}
      {/* <div className="mt-2 flex shrink-0 gap-2 px-4 pb-4">
        <button
          onClick={() => setPageNumber((p) => Math.max(1, p - 1))}
          disabled={pageNumber <= 1}
          className="rounded bg-gray-700 px-2 py-1 text-white"
        >
          Prev
        </button>
        <span className="text-gray-200">
          Page {pageNumber} of {numPages}
        </span>
        <button
          onClick={() => setPageNumber((p) => Math.min(numPages || 1, p + 1))}
          disabled={numPages ? pageNumber >= numPages : true}
          className="rounded bg-gray-700 px-2 py-1 text-white"
        >
          Next
        </button>
      </div> */}
    </div>
  );
}
