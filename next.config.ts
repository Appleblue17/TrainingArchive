import type { NextConfig } from "next";
const isProd = process.env.NODE_ENV === "production";

const nextConfig: NextConfig = {
  /* config options here */
  ...(isProd && {
    output: "export",
    basePath: "/Training-Archive",
    assetPrefix: "/Training-Archive/",
  }),
};

export default nextConfig;
