import { useEffect, useState } from "react";

import { getRooms } from "../services/api";

import RoomCard from "../components/RoomCard";

export default function Rooms() {
  const [rooms, setRooms] = useState<any[]>([]);

  useEffect(() => {
    getRooms()
      .then(setRooms)
      .catch(console.error);
  }, []);

  return (
    <>
      <h1 className="text-4xl font-bold mb-8">
        Rooms
      </h1>

      <div className="grid grid-cols-1 md:grid-cols-2 xl:grid-cols-3 gap-4">

        {rooms.map((room) => (
          <RoomCard
            key={room.roomId}
            {...room}
          />
        ))}

      </div>
    </>
  );
}