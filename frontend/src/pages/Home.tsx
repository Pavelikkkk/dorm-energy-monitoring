import { Link } from "react-router-dom";

export default function Home() {
  return (<div className="w-full">

    {/* HERO */}

    <section
      className="
      min-h-[70vh]
      flex
      flex-col
      justify-center
      items-center
      text-center
    "
    >
      <div className="text-8xl mb-8">
        ⚡
      </div>

      <h1
        className="
        text-5xl
        md:text-7xl
        font-bold
        max-w-5xl
        mb-8
      "
      >
        The Future of Smart Monitoring
      </h1>

      <p
        className="
        text-xl
        text-slate-400
        max-w-3xl
        mb-10
      "
      >
        Real-time monitoring, machine learning
        anomaly detection and analytics platform
        for dormitories and smart buildings.
      </p>

      <div className="flex gap-4 flex-wrap">

        <Link
          to="/buildings"
          className="
          px-8
          py-4
          rounded-xl
          bg-orange-300
          text-slate-900
          font-semibold
        "
        >
          Open Platform
        </Link>

        <button
          disabled
          className="
          px-8
          py-4
          rounded-xl
          border
          border-slate-600
          text-slate-400
        "
        >
          Desktop App (Coming Soon)
        </button>

      </div>

    </section>

    {/* FEATURE 1 */}

    <section
      className="
      grid
      grid-cols-1
      xl:grid-cols-2
      gap-12
      py-24
      items-center
    "
    >
      <div>

        <h2 className="text-5xl font-bold mb-6">
          Real-Time Monitoring
        </h2>

        <p className="text-xl text-slate-400">
          ESP32 devices stream live power,
          motion and light measurements
          through MQTT.
        </p>

      </div>

      <div
        className="
        h-96
        bg-slate-800
        rounded-3xl
        border
        border-slate-700
        flex
        items-center
        justify-center
      "
      >
        Analytics Screenshot
      </div>

    </section>

    {/* FEATURE 2 */}

    <section
      className="
      grid
      grid-cols-1
      xl:grid-cols-2
      gap-12
      py-24
      items-center
    "
    >
      <div
        className="
        order-2
        xl:order-1
        h-96
        bg-slate-800
        rounded-3xl
        border
        border-slate-700
        flex
        items-center
        justify-center
      "
      >
        ML Detection Screenshot
      </div>

      <div className="order-1 xl:order-2">

        <h2 className="text-5xl font-bold mb-6">
          Hybrid Detection
        </h2>

        <p className="text-xl text-slate-400">
          Rule-based and ONNX-powered
          machine learning anomaly
          detection.
        </p>

      </div>

    </section>

    {/* FEATURE 3 */}

    <section
      className="
      grid
      grid-cols-1
      xl:grid-cols-2
      gap-12
      py-24
      items-center
    "
    >
      <div>

        <h2 className="text-5xl font-bold mb-6">
          Analytics Platform
        </h2>

        <p className="text-xl text-slate-400">
          Historical trends, room statistics,
          anomaly reports and energy insights.
        </p>

      </div>

      <div
        className="
        h-96
        bg-slate-800
        rounded-3xl
        border
        border-slate-700
        flex
        items-center
        justify-center
      "
      >
        Dashboard Preview
      </div>

    </section>

    {/* PROJECT OVERVIEW */}

    <section className="py-24">

      <h2 className="text-5xl font-bold text-center mb-16">
        Project Overview
      </h2>

      <div className="grid grid-cols-1 lg:grid-cols-3 gap-8">

        {/* ARCHITECTURE */}

        <div
          className="
        bg-slate-800
        border
        border-slate-700
        rounded-3xl
        p-10
        hover:border-orange-300
        transition
        "
        >

          <h3 className="text-4xl font-bold mb-10">
            Architecture
          </h3>

          <div
            className="
            flex
            flex-wrap
            items-center
            justify-center
            gap-3
            text-xl
        "
          >
            <div className="flex flex-col items-center">

              <div className="text-3xl font-semibold">
                📡 ESP32
              </div>

              <div className="text-white text-4xl my-1">
                ↓
              </div>

              <div className="text-3xl font-semibold">
                📨 MQTT
              </div>

              <div className="text-white text-4xl my-1">
                ↓
              </div>

              <div className="text-3xl font-semibold">
                ⚙️ Backend
              </div>

              <div className="text-white text-4xl my-1">
                ↓
              </div>

              <div className="text-3xl font-semibold">
                🗄️ TimescaleDB
              </div>

              <div className="text-white text-4xl my-1">
                ↓
              </div>

              <div className="text-3xl font-semibold">
                📊 Dashboard
              </div>

            </div>

          </div>
        </div>
        {/* PLATFORM */}

        <div
          className="
        bg-slate-800
        border
        border-slate-700
        rounded-3xl
        p-10
        hover:border-orange-300
        transition
      "
        >

          <h3 className="text-4xl font-bold mb-8">
            Platform
          </h3>

          <div className="space-y-5">

            <Link
              to="/buildings"
              className="
            block
            bg-slate-900
            rounded-xl
            p-5
            text-2xl
            font-semibold
            hover:bg-slate-700
            hover:text-orange-300
            transition
          "
            >
              🏢 Buildings
            </Link>

            <Link
              to="/devices"
              className="
            block
            bg-slate-900
            rounded-xl
            p-5
            text-2xl
            font-semibold
            hover:bg-slate-700
            hover:text-orange-300
            transition
          "
            >
              📡 Devices
            </Link>

            <Link
              to="/anomalies"
              className="
            block
            bg-slate-900
            rounded-xl
            p-5
            text-2xl
            font-semibold
            hover:bg-slate-700
            hover:text-orange-300
            transition
          "
            >
              ⚠️ Anomalies
            </Link>

            </div>

        </div>

        {/* STACK */}

        <div
          className="
        bg-slate-800
        border
        border-slate-700
        rounded-3xl
        p-10
        hover:border-orange-300
        transition
      "
        >

          <h3 className="text-4xl font-bold mb-10">
            Technology Stack
          </h3>

          <div className="space-y-6 text-2xl">

            <div>⚙️ C++20</div>

            <div>⚡ Drogon</div>

            <div>📨 MQTT</div>

            <div>🗄️ TimescaleDB</div>

            <div>⚛️ React</div>

            <div>🤖 ONNX Runtime</div>

          </div>

        </div>

      </div>

    </section>

    {/* FOOTER */}

    <footer
      className="
    border-t
    border-slate-700
    mt-24
    py-16
  "
    >

      <div
        className="
      grid
      grid-cols-1
      md:grid-cols-3
      gap-12
    "
      >

        <div>

          <div className="text-4xl mb-4">
            ⚡
          </div>

          <h3 className="text-2xl font-bold mb-3">
            Monitoring Platform
          </h3>

          <p className="text-slate-400">
            Smart IoT platform for energy monitoring,
            anomaly detection and analytics.
          </p>

        </div>

        <div>

          <h4 className="text-xl font-semibold mb-4">
            Links
          </h4>

          <div className="space-y-3 text-slate-400">

            <a
              href="https://github.com/Pavelikkkk/dorm-energy-monitoring"
              target="_blank"
              rel="noreferrer"
              className="block hover:text-orange-300"
            >
              GitHub
            </a>

            <a
              href="https://t.me/atcocoon"
              target="_blank"
              rel="noreferrer"
              className="block hover:text-orange-300"
            >
              Telegram
            </a>

          </div>

        </div>

      </div>

      <div
        className="
      mt-12
      pt-8
      border-t
      border-slate-800
      text-slate-500
      text-center
    "
      >
        Monitoring Platform • Version 2.0
      </div>

    </footer>

  </div>

  );
}
