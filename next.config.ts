import type { NextConfig } from "next";

const isProd = process.env.NODE_ENV === "production";
console.log("NODE_ENV:", process.env.NODE_ENV);

const nextConfig: NextConfig = {
  /* config options here */
  output: "export",
  basePath: "/Training-Archive",
  assetPrefix: "/Training-Archive/",
};

export default nextConfig;
