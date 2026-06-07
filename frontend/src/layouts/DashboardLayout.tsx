import Sidebar from "../components/Sidebar";
import DashboardHeader from "../components/DashboardHeader";

type Props = {
  children: React.ReactNode;
};

export default function DashboardLayout({
  children,
}: Props) {
  return (
    <div className="min-h-screen bg-slate-900 text-white">

      <DashboardHeader />

      <main
        className="
          max-w-[1600px]
          mx-auto
          px-6
          md:px-10
          lg:px-12
          pb-10
        "
      >
        {children}
      </main>

    </div>
  );
}