import { useEffect, useState } from "react";
import { getDevices } from "../services/api";

type Device = {
  deviceId: string;
  deviceName: string;
  deviceModel: string;
  firmwareVersion: string;
  roomName: string;
  isOnline: boolean;
  lastSeenAt: string;
};

export default function Devices() {
  const [devices, setDevices] =
    useState<Device[]>([]);

  useEffect(() => {
    loadDevices();
  }, []);

  async function loadDevices() {
    try {
      const data =
        await getDevices();

      setDevices(data);
    } catch (err) {
      console.error(err);
    }
  }

  return (
    <>
      <h1 className="text-4xl font-bold mb-8">
        Devices
      </h1>

      <div className="bg-slate-800 border border-slate-700 rounded-xl overflow-hidden">

        <table className="w-full">

          <thead className="bg-slate-700">

            <tr>
              <th className="p-4 text-left">
                Device
              </th>

              <th className="p-4 text-left">
                Room
              </th>

              <th className="p-4 text-left">
                Model
              </th>

              <th className="p-4 text-left">
                Firmware
              </th>

              <th className="p-4 text-left">
                Status
              </th>

            </tr>

          </thead>

          <tbody>

            {devices.map((device) => (
              <tr
                key={device.deviceId}
                className="border-t border-slate-700"
              >
                <td className="p-4">
                  {device.deviceName}
                </td>

                <td className="p-4">
                  {device.roomName}
                </td>

                <td className="p-4">
                  {device.deviceModel}
                </td>

                <td className="p-4">
                  {device.firmwareVersion}
                </td>

                <td className="p-4">
                  <span
                    className={
                      device.isOnline
                        ? "text-green-400"
                        : "text-red-400"
                    }
                  >
                    {device.isOnline
                      ? "Online"
                      : "Offline"}
                  </span>
                </td>

              </tr>
            ))}

          </tbody>

        </table>

      </div>
    </>
  );
}