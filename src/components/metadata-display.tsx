import { FileMetadataType } from "@/lib/types";

// Helper function: format key name
export function formatKey(key: string) {
  return key.replace(/_/g, " ").replace(/\b\w/g, (c) => c.toUpperCase());
}

// Helper function: format bytes
export function formatSize(size: number) {
  if (size < 1024) return `${size} B`;
  if (size < 1024 * 10) return `${(size / 1024).toFixed(3)} KB (${size} B)`;
  if (size < 1024 * 1024) return `${(size / 1024).toFixed(2)} KB`;
  return `${(size / 1024 / 1024).toFixed(2)} MB`;
}

// Helper function: format date
export function formatDate(val: unknown) {
  const d = typeof val === "string" ? new Date(val) : val;
  if (d instanceof Date && !isNaN(d.getTime())) {
    return d
      .toLocaleString("zh-CN", {
        year: "numeric",
        month: "2-digit",
        day: "2-digit",
        hour: "2-digit",
        minute: "2-digit",
        second: "2-digit",
        hour12: false,
      })
      .replace(/-/g, "/");
  }
  return String(val);
}

export default function MetaDataDisplay({
  name,
  metadata,
  metadataBanner = [],
}: {
  name?: string;
  metadata: FileMetadataType;
  metadataBanner?: string[];
}) {
  if (!metadata) return null;

  return (
    <div className="overflow-auto">
      {name && <h2 className="px-1 py-1 text-sm font-medium text-gray-300">{name}</h2>}
      <div className="rounded border-2 border-gray-400 bg-black/80 p-3 font-mono text-sm text-green-300">
        {Object.entries(metadata).map(([key, value]) => {
          if (metadataBanner.includes(key)) {
            return null; // Skip keys in the banner
          }
          const keyDisplay = <span className="text-blue-400">[{formatKey(key)}]</span>;
          let valueDisplay;
          if (key === "size" && typeof value === "number") {
            valueDisplay = <span className="text-yellow-400">{formatSize(value)}</span>;
          } else if (key.includes("time_limit") && typeof value === "number") {
            // unit: seconds
            valueDisplay = <span className="text-yellow-400">{value} s</span>;
          } else if (key.includes("memory_limit") && typeof value === "number") {
            // unit: kilobytes
            valueDisplay = <span className="text-yellow-400">{value} MB</span>;
          } else if (key.includes("time")) {
            valueDisplay = <span className="text-pink-400">{formatDate(value)}</span>;
          } else if (
            (key.includes("date") || key.includes("duration")) &&
            typeof value === "string"
          ) {
            valueDisplay = <span className="text-pink-400">{value}</span>;
          } else if (key.includes("link") && typeof value === "string") {
            valueDisplay = (
              <a
                href={value}
                target="_blank"
                rel="noopener noreferrer"
                className="text-indigo-400 underline hover:text-indigo-200"
              >
                {value}
              </a>
            );
          } else if (typeof value === "number") {
            valueDisplay = <span className="text-yellow-300">{value}</span>;
          } else if (typeof value === "boolean") {
            valueDisplay = <span className="text-cyan-400">{value ? "true" : "false"}</span>;
          } else if (typeof value === "object" && value !== null) {
            valueDisplay = <span className="text-gray-400">{JSON.stringify(value)}</span>;
          } else {
            valueDisplay = <span className="text-green-200">{String(value)}</span>;
          }
          return (
            <div
              key={key}
              className="mb-1 break-all"
              style={{ textIndent: "-1.2em", paddingLeft: "1.2em" }}
            >
              {keyDisplay} {valueDisplay}
            </div>
          );
        })}
      </div>
    </div>
  );
}
