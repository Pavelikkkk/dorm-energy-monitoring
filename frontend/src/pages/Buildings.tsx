import { useEffect, useState } from "react";
import { Link } from "react-router-dom";

import { getBuildings } from "../services/api";

type Building = {
  id: number;
  name: string;
  address: string;
  description: string;
};

export default function Buildings() {
  const [buildings, setBuildings] =
    useState<Building[]>([]);

  useEffect(() => {
    loadBuildings();
  }, []);

  async function loadBuildings() {
    try {
      const data =
        await getBuildings();

      setBuildings(data);
    }
    catch (err) {
      console.error(err);
    }
  }

  return (
    <>
      <h1 className="text-4xl font-bold mb-8">
        Buildings
      </h1>

      <div className="grid gap-6">

        {buildings.map((building) => (
          <Link
            key={building.id}
            to={`/buildings/${building.id}`}
            className="
              block
              bg-slate-800
              border
              border-slate-700
              rounded-xl
              p-6
              hover:border-cyan-500
              hover:bg-slate-750
              transition
            "
          >
            <h2 className="text-2xl font-bold text-cyan-400 mb-2">
              {building.name}
            </h2>

            <p className="text-slate-300 mb-2">
              📍 {building.address}
            </p>

            <p className="text-slate-400 mb-4">
              {building.description}
            </p>

            <div className="text-cyan-400 text-sm font-semibold">
              View Building →
            </div>
          </Link>
        ))}

      </div>
    </>
  );
}