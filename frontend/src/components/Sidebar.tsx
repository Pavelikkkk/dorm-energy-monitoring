import { Link } from "react-router-dom";
import { useState } from "react";

export default function Sidebar() {
    const [open, setOpen] =
        useState(false);

    return (
        <>
            {/* MENU BUTTON */}

            <button
                onClick={() => setOpen(true)}
                className="
            w-12
            h-12
            rounded-xl
            bg-slate-800
            border
            border-slate-700
            hover:bg-slate-700
            transition
        "
            >
                ☰
            </button>

            {/* SIDEBAR */}

            {open && (
                <div
                    className="
            fixed
            inset-0
            z-50
            bg-black/60
            backdrop-blur-sm
          "
                >
                    <aside
                        className="
              w-80
              h-screen
              bg-slate-950
              border-r
              border-slate-800
              p-6
              flex
              flex-col
            "
                    >
                        {/* HEADER */}

                        <div
                            className="
                flex
                justify-between
                items-center
                mb-10
              "
                        >
                            <Link
                                to="/"
                                className="
                  flex
                  items-center
                  gap-3
                "
                                onClick={() =>
                                    setOpen(false)
                                }
                            >
                                <span className="text-4xl">
                                    ⚡
                                </span>

                                <span
                                    className="
                    text-xl
                    font-bold
                  "
                                >
                                    Monitoring System
                                </span>
                            </Link>

                            <button
                                onClick={() =>
                                    setOpen(false)
                                }
                                className="
                  text-2xl
                  hover:text-orange-300
                "
                            >
                                ✕
                            </button>
                        </div>

                        {/* NAVIGATION */}

                        <div className="space-y-4 text-lg">

                            <Link
                                to="/buildings"
                                onClick={() =>
                                    setOpen(false)
                                }
                                className="block hover:text-orange-300"
                            >
                                🏢 Buildings
                            </Link>

                            <Link
                                to="/devices"
                                onClick={() =>
                                    setOpen(false)
                                }
                                className="block hover:text-orange-300"
                            >
                                📡 Devices
                            </Link>

                            <Link
                                to="/anomalies"
                                onClick={() =>
                                    setOpen(false)
                                }
                                className="block hover:text-orange-300"
                            >
                                ⚠️ Anomalies
                            </Link>

                        </div>
                    </aside>
                </div>
            )}
        </>
    );
}