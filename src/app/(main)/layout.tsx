import Breadcrumb from "./breadcrumb";

export default async function Layout({ children }: { children: React.ReactNode }) {
  return (
    <div className="mt-4 flex min-h-screen min-w-[1600px] justify-center">
      <div className="mx-auto w-3/4 -translate-x-10">
        <header className="w-full rounded-lg py-4 text-slate-300">
          <h1 className="text-3xl font-semibold tracking-wide">Training Archive</h1>
        </header>
        <Breadcrumb />
        <main className="mt-4">{children}</main>
      </div>
    </div>
  );
}
