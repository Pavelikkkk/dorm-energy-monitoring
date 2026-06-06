import type { Anomaly } from "../types/anomaly";
import type { DashboardStats } from "../types/stats";

export const dashboardStats: DashboardStats = {
  rooms: 6,
  alerts: 18,
  mlAlerts: 6,
  mqttOnline: true,
};

export const anomalies: Anomaly[] = [
  {
    id: 1,
    roomId: "Kitchen",
    anomalyType: "ml_anomaly",
    severity: "WARNING",
    score: 0.93,
    description: "Autoencoder reconstruction error",
    detectedAt: "2026-06-05T12:00:00",
    acknowledged: false,
  },

  {
    id: 2,
    roomId: "Bathroom",
    anomalyType: "rule_power_without_motion",
    severity: "WARNING",
    description: "Power usage detected",
    detectedAt: "2026-06-05T12:03:00",
    acknowledged: false,
  },
];