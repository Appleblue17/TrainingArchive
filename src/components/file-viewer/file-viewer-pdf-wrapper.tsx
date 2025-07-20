"use client";
import dynamic from "next/dynamic";
const FileViewerPDF = dynamic(() => import("./file-viewer-pdf"), { ssr: false });

export default function FileViewerPDFWrapper({ pdfPath }: { pdfPath: string }) {
  return <FileViewerPDF pdfPath={pdfPath} />;
}
