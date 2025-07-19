"use client";
import { useState } from "react";
import { FiCode } from "react-icons/fi";
import SyntaxHighlighter from "react-syntax-highlighter";
import { atomOneDark } from "react-syntax-highlighter/dist/esm/styles/hljs";

export default function FileViewerSource({ code, ext }: { code: string; ext: string }) {
  const [copied, setCopied] = useState(false);

  const handleCopy = async () => {
    await navigator.clipboard.writeText(code);
    setCopied(true);
    setTimeout(() => setCopied(false), 1200);
  };

  return (
    <div className="relative flex h-[85dvh] w-[60dvw] min-w-0 max-w-full flex-col overflow-y-auto rounded border-2 border-gray-600 bg-zinc-900">
      <div className="absolute left-4 top-0">
        <FiCode className="mr-1 inline-block text-gray-200" />
        <span className="text-sm text-gray-400">{ext.slice(1)}</span>
      </div>
      <button
        onClick={handleCopy}
        className="absolute right-6 top-4 z-10 rounded bg-gray-700 px-4 py-1 text-sm text-white hover:bg-gray-600"
      >
        {copied ? "Copied!" : "Copy"}
      </button>
      <div className="flex-1 py-5">
        <SyntaxHighlighter
          language={ext.slice(1)}
          style={atomOneDark}
          showLineNumbers
          customStyle={{
            background: "transparent",
          }}
          lineNumberStyle={{
            paddingRight: "10px",
            marginRight: "15px",
            color: "#888",
            borderRight: "1px solid #444",
          }}
        >
          {code}
        </SyntaxHighlighter>
      </div>
    </div>
  );
}
