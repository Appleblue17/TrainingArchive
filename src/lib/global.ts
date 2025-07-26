const isProd = process.env.NODE_ENV === "production";

export const BASE_URL = isProd
  ? "https://appleblue17.github.io/Training-Archive/"
  : "http://localhost:3000/";

export const PREFIX_URL = isProd ? "/Training-Archive" : "/";

export const allowedExtensions = [
  ".pdf",
  ".md",
  ".txt",
  ".js",
  ".ts",
  ".tsx",
  ".jsx",
  ".py",
  ".cpp",
  ".c",
  ".h",
  ".hpp",
  ".java",
  ".json",
  ".yml",
  ".yaml",
  ".sh",
  ".bat",
  ".go",
  ".rs",
  ".cs",
  ".html",
  ".css",
  ".xml",
];
