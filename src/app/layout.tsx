import "@/lib/globals.css";
import { inter } from "../../public/fonts/fonts";

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="en" suppressHydrationWarning>
      <head></head>
      <body className={`${inter.className} antialiased`}>{children}</body>
    </html>
  );
}
