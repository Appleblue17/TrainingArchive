"use client";
import { useState } from "react";
import "@public/github-markdown-dark.css";
import "@public/katex.min.css";
import "@public/github-dark.css";
import { FiCopy } from "react-icons/fi";

export default function FileViewerMarkdown({
  raw,
  htmlContent,
}: {
  raw: string;
  htmlContent: string;
}) {
  const [copyMessage, setCopyMessage] = useState("Copy");

  const handleCopy = async () => {
    if (typeof navigator !== "undefined" && navigator.clipboard) {
      await navigator.clipboard.writeText(raw);
      setCopyMessage("Copied!");
      setTimeout(() => setCopyMessage("Copy"), 1200);
    } else {
      setCopyMessage("Clipboard API unavailable");
      setTimeout(() => setCopyMessage("Copy"), 2000);
    }
  };

  return (
    <div className="relative flex h-[85dvh] w-full min-w-0 max-w-full flex-col rounded border-2 border-gray-600 bg-[#0d1117]">
      <button
        onClick={handleCopy}
        className="absolute right-6 top-4 z-10 rounded bg-gray-700 px-3 py-1 text-sm text-white hover:bg-gray-600"
      >
        <FiCopy className="mr-1 inline-block" />
        {copyMessage}
      </button>
      <div className="flex-1 overflow-y-auto">
        <div className="markdown-body p-12" dangerouslySetInnerHTML={{ __html: htmlContent }} />
      </div>
    </div>
  );
}
