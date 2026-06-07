import { useEffect, useState } from "react";

import {
  ResponsiveContainer,
  PieChart,
  Pie,
  Tooltip,
  Cell,
} from "recharts";

import {
  getAnomalyStatistics,
} from "../services/api";

const COLORS = [
  "#06b6d4",
  "#22c55e",
  "#f59e0b",
  "#ef4444",
];

export default function AnomaliesChart() {
  const [data, setData] =
    useState<any[]>([]);

  useEffect(() => {
    getAnomalyStatistics()
      .then(setData)
      .catch(console.error);
  }, []);

  return (
    <div className="bg-slate-800 border border-slate-700 rounded-xl p-6">

      <h2 className="text-2xl font-bold mb-6">
        Anomalies By Type
      </h2>

      <div style={{ height: 300 }}>

        <ResponsiveContainer>

          <PieChart>

            <Pie
              data={data}
              dataKey="count"
              nameKey="type"
              outerRadius={100}
              label
            >
              {data.map((_, index) => (
                <Cell
                  key={index}
                  fill={
                    COLORS[
                      index %
                        COLORS.length
                    ]
                  }
                />
              ))}
            </Pie>

            <Tooltip />

          </PieChart>

        </ResponsiveContainer>

      </div>

    </div>
  );
}