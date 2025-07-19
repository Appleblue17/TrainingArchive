import Link from "next/link";

export default function Breadcrumb() {
  return (
    <nav className="flex w-full items-center rounded-lg bg-gray-700 px-4 py-2 shadow">
      <div className="flex items-center space-x-2 text-sm">
        <Link href="/" className="text-base font-medium text-blue-300">
          Home
        </Link>
      </div>
    </nav>
  );
}
