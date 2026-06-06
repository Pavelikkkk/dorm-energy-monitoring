type Props = {
  roomId: string;
  power: number;
  light: number;
  motion: boolean;
  status: "NORMAL" | "WARNING" | "CRITICAL";
};

export default function RoomCard({
  roomId,
  power,
  light,
  motion,
  status,
}: Props) {
  const statusColor = {
    NORMAL: "text-green-400",
    WARNING: "text-yellow-400",
    CRITICAL: "text-red-400",
  };

  return (
    <div className="bg-slate-800 border border-slate-700 rounded-xl p-5">
      <div className="flex justify-between mb-4">
        <h2 className="font-bold text-xl">
          🏠 {roomId}
        </h2>

        <span className={statusColor[status]}>
          {status}
        </span>
      </div>

      <div className="space-y-2 text-slate-300">
        <p>⚡ Power: {power} W</p>
        <p>💡 Light: {light} lx</p>
        <p>🚶 Motion: {motion ? "Yes" : "No"}</p>
      </div>
    </div>
  );
}