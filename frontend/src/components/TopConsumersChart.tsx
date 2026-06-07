import { useEffect, useState } from "react";

import {
  ResponsiveContainer,
  BarChart,
  Bar,
  XAxis,
  YAxis,
  Tooltip,
} from "recharts";

import {
  getTopConsumers,
} from "../services/api";

export default function TopConsumersChart() {
  const [data, setData] =
    useState<any[]>([]);

  useEffect(() => {
    getTopConsumers()
      .then(setData)
      .catch(console.error);
  }, []);

  return (
    <div className="bg-slate-800 border border-slate-700 rounded-xl p-6">

      <h2 className="text-2xl font-bold mb-6">
        Top Power Consumers
      </h2>

      <div style={{ height: 300 }}>

        <ResponsiveContainer>

          <BarChart data={data}>

            <XAxis
              dataKey="roomName"
              stroke="#94a3b8"
            />

            <YAxis
              stroke="#94a3b8"
            />

            <Tooltip />

            <Bar
              dataKey="power"
              fill="#06b6d4"
            />

          </BarChart>

        </ResponsiveContainer>

      </div>

    </div>
  );
}