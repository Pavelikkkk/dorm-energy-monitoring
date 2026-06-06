import { BrowserRouter, Routes, Route } from "react-router-dom";

import MainLayout from "./layouts/MainLayout";

import Home from "./pages/Home";
import Analytics from "./pages/Analytics";
import Buildings from "./pages/Buildings";
import Devices from "./pages/Devices";
import Anomalies from "./pages/Anomalies";

export default function App() {
  return (
    <BrowserRouter>
      <MainLayout>
        <Routes>
          <Route path="/" element={<Home />} />

          <Route
            path="/buildings"
            element={<Buildings />}
          />

          <Route
            path="/analytics"
            element={<Analytics />}
          />

          <Route
            path="/devices"
            element={<Devices />}
          />

          <Route
            path="/anomalies"
            element={<Anomalies />}
          />
        </Routes>
      </MainLayout>
    </BrowserRouter>
  );
}