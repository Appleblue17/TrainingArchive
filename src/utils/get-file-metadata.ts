import fs from "fs";
import path from "path";
import { FileMetadataType } from "@/lib/types";

export default function getFileMetadata(filePath: string, metadataPath: string): FileMetadataType {
  const stats = fs.statSync(filePath);

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
