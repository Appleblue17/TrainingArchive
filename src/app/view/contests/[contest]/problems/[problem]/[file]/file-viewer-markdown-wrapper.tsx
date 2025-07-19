import rehypeKatex from "rehype-katex";
import rehypeSanitize from "rehype-sanitize";
import rehypeStringify from "rehype-stringify";
import rehypeFormat from "rehype-format";
import remarkMath from "remark-math";
import remarkGfm from "remark-gfm";
import remarkParse from "remark-parse";
import remarkRehype from "remark-rehype";
import rehypeHighlight from "rehype-highlight";
import remarkImgLinks from "@pondorasti/remark-img-links";

import { unified } from "unified";
import FileViewerMarkdown from "./file-viewer-markdown";

export default async function FileViewerMarkdownWrapper({
  dirPath,
  raw,
}: {
  dirPath: string;
  raw: string;
}) {
  const mathRegex = /\$\$([^$\n]*)\$\$/;
  const rawWithMath = raw.replace(mathRegex, "$$$$\n$1\n$$$$\n");

  const file = await unified()
    .use(remarkParse)
    .use(remarkMath)
    .use(remarkGfm)
    .use(remarkImgLinks, { absolutePath: dirPath + "/" })
    .use(remarkRehype)
    .use(rehypeSanitize)
    .use(rehypeHighlight, { detect: true })
    .use(rehypeKatex)
    .use(rehypeFormat)
    .use(rehypeStringify)
    .process(rawWithMath);

  return <FileViewerMarkdown raw={raw} htmlContent={String(file.value)} />;
}
