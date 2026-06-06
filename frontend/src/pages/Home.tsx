export default function Home() {
  return (
    <div className="space-y-12">
      {/* Hero */}

      <section className="py-10">
        <h1 className="text-5xl font-bold mb-6">
          Dorm Energy Monitoring
        </h1>

        <p className="text-xl text-slate-300 max-w-3xl leading-relaxed">
          Real-time energy analytics and anomaly detection
          platform for dormitories and smart buildings.
        </p>

        <div className="flex flex-wrap gap-4 mt-8">
          <div className="bg-cyan-500/10 border border-cyan-500 rounded-lg px-4 py-2">
            MQTT Streaming
          </div>

          <div className="bg-cyan-500/10 border border-cyan-500 rounded-lg px-4 py-2">
            TimescaleDB
          </div>

          <div className="bg-cyan-500/10 border border-cyan-500 rounded-lg px-4 py-2">
            ONNX ML Detection
          </div>

          <div className="bg-cyan-500/10 border border-cyan-500 rounded-lg px-4 py-2">
            Telegram Alerts
          </div>
        </div>
      </section>

      {/* Features */}

      <section>
        <h2 className="text-3xl font-bold mb-6">
          Platform Features
        </h2>

        <div className="grid grid-cols-1 md:grid-cols-2 xl:grid-cols-4 gap-6">
          <div className="bg-slate-800 border border-slate-700 rounded-xl p-6">
            <h3 className="text-xl font-semibold mb-2">
              Real-Time Monitoring
            </h3>

            <p className="text-slate-400">
              Live MQTT sensor stream processing and
              room state aggregation.
            </p>
          </div>

          <div className="bg-slate-800 border border-slate-700 rounded-xl p-6">
            <h3 className="text-xl font-semibold mb-2">
              Anomaly Detection
            </h3>

            <p className="text-slate-400">
              Rule-based and ONNX-powered machine
              learning anomaly detection.
            </p>
          </div>

          <div className="bg-slate-800 border border-slate-700 rounded-xl p-6">
            <h3 className="text-xl font-semibold mb-2">
              Energy Analytics
            </h3>

            <p className="text-slate-400">
              Historical consumption trends and
              power usage visualization.
            </p>
          </div>

          <div className="bg-slate-800 border border-slate-700 rounded-xl p-6">
            <h3 className="text-xl font-semibold mb-2">
              Notifications
            </h3>

            <p className="text-slate-400">
              Instant Telegram notifications for
              critical incidents and alerts.
            </p>
          </div>
        </div>
      </section>

      {/* Architecture */}

      <section>
        <h2 className="text-3xl font-bold mb-6">
          System Architecture
        </h2>

        <div className="bg-slate-800 border border-slate-700 rounded-xl p-8">
          <div className="flex flex-col xl:flex-row items-center justify-between gap-6 text-center">
            <div>
              <div className="text-3xl mb-2">📡</div>
              <div className="font-semibold">
                ESP32 Sensors
              </div>
            </div>

            <div className="text-cyan-400 text-2xl">
              →
            </div>

            <div>
              <div className="text-3xl mb-2">📨</div>
              <div className="font-semibold">
                MQTT Broker
              </div>
            </div>

            <div className="text-cyan-400 text-2xl">
              →
            </div>

            <div>
              <div className="text-3xl mb-2">⚙️</div>
              <div className="font-semibold">
                Drogon Backend
              </div>
            </div>

            <div className="text-cyan-400 text-2xl">
              →
            </div>

            <div>
              <div className="text-3xl mb-2">🗄️</div>
              <div className="font-semibold">
                TimescaleDB
              </div>
            </div>

            <div className="text-cyan-400 text-2xl">
              →
            </div>

            <div>
              <div className="text-3xl mb-2">📊</div>
              <div className="font-semibold">
                Analytics Platform
              </div>
            </div>
          </div>
        </div>
      </section>

      {/* Technologies */}

      <section>
        <h2 className="text-3xl font-bold mb-6">
          Technology Stack
        </h2>

        <div className="grid grid-cols-2 md:grid-cols-3 xl:grid-cols-6 gap-4">
          {[
            "C++20",
            "Drogon",
            "MQTT",
            "TimescaleDB",
            "React",
            "ONNX Runtime",
          ].map((tech) => (
            <div
              key={tech}
              className="
                bg-slate-800
                border
                border-slate-700
                rounded-lg
                p-4
                text-center
                font-semibold
              "
            >
              {tech}
            </div>
          ))}
        </div>
      </section>
    </div>
  );
}