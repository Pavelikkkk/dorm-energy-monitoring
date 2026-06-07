import { useParams, Link } from "react-router-dom";
import { useEffect, useState } from "react";

import {
  getBuildings,
  getRooms,
  getDevices,
} from "../services/api";

export default function BuildingDetails() {
  const { id } = useParams();

  const [building, setBuilding] =
    useState<any>(null);

  const [rooms, setRooms] =
    useState<any[]>([]);

  const [devices, setDevices] =
    useState<any[]>([]);

  const [search, setSearch] =
    useState("");

  const [visibleRooms, setVisibleRooms] =
    useState(12);

  useEffect(() => {
    loadData();
  }, []);

  async function loadData() {
    try {
      const [
        buildings,
        roomsData,
        devicesData,
      ] = await Promise.all([
        getBuildings(),
        getRooms(),
        getDevices(),
      ]);

      const currentBuilding =
        buildings.find(
          (b: any) =>
            String(b.id) === id
        );

      setBuilding(currentBuilding);

      setRooms(
        roomsData.filter(
          (r: any) =>
            String(r.buildingId) === id
        )
      );

      setDevices(devicesData);
    }
    catch (error) {
      console.error(error);
    }
  }

  if (!building) {
    return (
      <div>
        Loading...
      </div>
    );
  }

  const filteredRooms =
    rooms.filter((room) =>
      room.roomName
        .toLowerCase()
        .includes(
          search.toLowerCase()
        )
    );

  return (
    <div className="space-y-8">

      {/* HEADER */}

      <div>

        <h1 className="text-5xl font-bold mb-3">
          {building.name}
        </h1>

        <p className="text-slate-400">
          {building.address}
        </p>

      </div>

      {/* STATS */}

      <div
        className="
          grid
          grid-cols-1
          md:grid-cols-3
          gap-4
        "
      >

        <div
          className="
            bg-slate-800
            rounded-2xl
            p-6
          "
        >
          <p className="text-slate-400">
            🚪 Rooms
          </p>

          <h2 className="text-3xl font-bold text-orange-200">
            {rooms.length}
          </h2>
        </div>

        <div
          className="
            bg-slate-800
            rounded-2xl
            p-6
          "
        >
          <p className="text-slate-400">
            📡 Devices
          </p>

          <h2 className="text-3xl font-bold text-cyan-300">
            {devices.length}
          </h2>
        </div>

        <div
          className="
            bg-slate-800
            rounded-2xl
            p-6
          "
        >
          <p className="text-slate-400">
            ⚡ Status
          </p>

          <h2 className="text-3xl font-bold text-green-400">
            ACTIVE
          </h2>
        </div>

      </div>

      {/* ANALYTICS */}

      <Link
        to={`/buildings/${id}/analytics`}
        className="
          block
          bg-orange-300
          text-slate-900
          rounded-2xl
          p-5
          font-semibold
          text-center
          hover:bg-orange-200
          transition
        "
      >
        Open Analytics →
      </Link>

      {/* SEARCH */}

      <input
        type="text"
        placeholder="Search room..."
        value={search}
        onChange={(e) =>
          setSearch(
            e.target.value
          )
        }
        className="
          w-full
          bg-slate-800
          border
          border-slate-700
          rounded-2xl
          p-5
          outline-none
          focus:border-orange-300
        "
      />

      {/* ROOMS */}

      <div>

        <h2 className="text-3xl font-bold mb-5">
          Rooms
        </h2>

        <div
          className="
            grid
            grid-cols-1
            md:grid-cols-2
            xl:grid-cols-3
            gap-5
          "
        >

          {filteredRooms
            .slice(
              0,
              visibleRooms
            )
            .map((room) => (

              <div
                key={room.id}
                className="
                  bg-slate-800
                  border
                  border-slate-700
                  rounded-2xl
                  p-5
                  hover:border-orange-300
                  transition
                "
              >

                <h3
                  className="
                    text-xl
                    font-bold
                    mb-2
                  "
                >
                  {room.roomName}
                </h3>

                <p className="text-slate-400 mb-4">
                  {room.roomType}
                </p>

                <div className="space-y-2">

                  <div>
                    🏢 Floor{" "}
                    {room.floorNumber}
                  </div>

                  <div>
                    📡 Devices:{" "}
                    {
                      devices.filter(
                        (d: any) =>
                          d.roomId ===
                          room.id
                      ).length
                    }
                  </div>

                </div>

              </div>

            ))}

        </div>

      </div>

      {/* SHOW MORE */}

      {visibleRooms <
        filteredRooms.length && (
          <div className="flex justify-center">

            <button
              onClick={() =>
                setVisibleRooms(
                  visibleRooms + 12
                )
              }
              className="
              px-8
              py-4
              rounded-xl
              bg-orange-300
              text-slate-900
              font-semibold
              hover:bg-orange-200
              transition
            "
            >
              Show More
            </button>

          </div>
        )}

    </div>
  );
}