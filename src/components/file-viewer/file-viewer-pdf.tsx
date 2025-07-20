import { PREFIX_URL } from "@/lib/global";
import path from "path";
import { useRef, useEffect, useState } from "react";
import { FiMinus, FiPlus } from "react-icons/fi";
import { Document, Page, pdfjs } from "react-pdf";
import "react-pdf/dist/Page/AnnotationLayer.css";
import "react-pdf/dist/Page/TextLayer.css";

export default function FileViewerPDF({ pdfPath }: { pdfPath: string }) {
  useEffect(() => {
    pdfjs.GlobalWorkerOptions.workerSrc = path.join(PREFIX_URL, "pdf.worker.min.mjs");
  }, []);

  const [numPages, setNumPages] = useState<number>();
  const [pageNumber, setPageNumber] = useState<number>(1);
  const [scale, setScale] = useState(0.8);
  const containerRef = useRef<HTMLDivElement>(null);
  const [containerWidth, setContainerWidth] = useState(600);
  const [inputPage, setInputPage] = useState(pageNumber);
  const [pendingScroll, setPendingScroll] = useState<number | null>(null);

  // Set the initial container width
  useEffect(() => {
    if (containerRef.current) {
      setContainerWidth(containerRef.current.offsetWidth - 36); // Subtracting padding
    }
  }, []);

  // Record the references to each page
  const pageRefs = useRef<(HTMLDivElement | null)[]>([]);
  useEffect(() => {
    if (pageRefs.current[pageNumber - 1]) {
      pageRefs.current[pageNumber - 1]?.scrollIntoView({ block: "start" });
    }
  }, [pageNumber]);

  // Update the page number based on scroll position
  const updatePageNum = () => {
    const container = containerRef.current;
    if (!container) return;
    const scrollTop = container.scrollTop;
    let closestPage = 1;
    let minDiff = Infinity;
    pageRefs.current.forEach((el, idx) => {
      if (el) {
        // Calculate the difference between the top of the element and the scroll position
        const diff = Math.abs(el.offsetTop - scrollTop);
        if (diff < minDiff) {
          minDiff = diff;
          closestPage = idx + 1;
        }
      }
    });
    setInputPage(closestPage);
  };

  useEffect(() => {
    const container = containerRef.current;
    if (!container) return;

    container.addEventListener("scroll", updatePageNum);
    return () => container.removeEventListener("scroll", updatePageNum);
  }, [numPages, scale, containerWidth]);

  const handleScaleChange = (newScale: number) => {
    if (containerRef.current && pageRefs.current[inputPage - 1]) {
      const container = containerRef.current;
      const pageEl = pageRefs.current[inputPage - 1] || document.createElement("div");
      // Record the current page's position in the viewport
      const offset = pageEl.offsetTop - container.scrollTop;
      setScale(newScale);
      setPendingScroll(offset);
    } else {
      setScale(newScale);
    }
  };

  useEffect(() => {
    if (pendingScroll !== null && containerRef.current && pageRefs.current[inputPage - 1]) {
      const container = containerRef.current;
      const pageEl = pageRefs.current[inputPage - 1] || document.createElement("div");
      // Resume the current page's position in the viewport
      container.scrollTop = pageEl.offsetTop - pendingScroll;
      setPendingScroll(null);
    }
  }, [scale, inputPage, pendingScroll]);

  function onDocumentLoadSuccess({ numPages }: { numPages: number }): void {
    setNumPages(numPages);
  }

  return (
    <div className="flex h-[85dvh] w-full flex-col rounded border-2 border-gray-600 bg-zinc-800">
      {/* Header */}
      <div className="flex shrink-0 items-center justify-center py-1">
        <div className="flex items-center gap-1 px-2">
          <button
            onClick={() => handleScaleChange(Math.max(0.5, scale - 0.1))}
            className="rounded px-2 py-2 text-white hover:bg-zinc-700"
          >
            <FiMinus className="size-4" />
          </button>
          <button
            onClick={() => handleScaleChange(Math.min(1, scale + 0.1))}
            className="rounded px-2 py-2 text-white hover:bg-zinc-700"
          >
            <FiPlus className="size-4" />
          </button>
        </div>
        <div className="flex items-center gap-1 border-l border-gray-600 px-2">
          <input
            type="text"
            value={inputPage}
            min={1}
            max={numPages || 1}
            onChange={(e) => setInputPage(Number(e.target.value))}
            onBlur={() => {
              updatePageNum();
            }}
            onKeyDown={(e) => {
              if (e.key === "Enter") {
                if (inputPage >= 1 && inputPage <= (numPages || 1) && inputPage !== pageNumber) {
                  setPageNumber(inputPage);
                }
              }
            }}
            className="mx-2 w-10 rounded bg-gray-700 py-1 text-center font-sans text-white"
          />
          <span className="text-sm text-gray-200">of {numPages}</span>
        </div>
      </div>

      {/* PDF Content  */}
      <div
        ref={containerRef}
        className="scrollbar-thin flex flex-1 items-start justify-center overflow-auto px-4"
      >
        <Document file={pdfPath} onLoadSuccess={onDocumentLoadSuccess}>
          {Array.from({ length: numPages || 0 }, (_, i) => (
            <div
              key={i + 1}
              ref={(el) => {
                pageRefs.current[i] = el;
              }}
              style={{
                marginBottom: i === (numPages || 1) - 1 ? 0 : `${containerWidth * scale * 0.02}px`,
              }}
              className="flex justify-center"
            >
              <Page
                pageNumber={i + 1}
                width={containerWidth ? Math.floor(containerWidth * scale) : undefined}
              />
            </div>
          ))}
        </Document>
      </div>
    </div>
  );
}
