# architecture

The repo is split into four layers:

- `include/tauri_cpp` and `src` hold the public C++ API and the core runtime model
- `rust/host` holds the shared Rust side of the bridge and Tauri-facing helpers
- `examples/*` hold the frontend examples and thin Tauri app crates
- `docs_site` publishes the public docs to GitHub Pages

## Ownership boundaries

- C++ owns app setup concepts, command registration, event emission, and the core runtime model
- Rust stays thin and mainly translates between Tauri and the C++ core
- the example apps own frontend assets and the immediate Tauri shell wiring
- `docs_site` is the public source for the hosted documentation

## Control path

The actual native control path is:

`frontend -> Rust command -> rust/host bridge -> C++`

That means the frontend should stay focused on UI and small command payloads, Rust should stay focused on command wiring and translation, and C++ should keep the heavier native logic.

## Key native files

- `src/app_builder.cpp`
- `src/event_bus.cpp`
- `rust/host/cpp/demo_bridge.cpp`

## Stable path

The stable path is a standalone desktop app that ships static frontend files in a Tauri webview. In development, `tauri dev` can use a local Vite server. In packaged apps, the webview loads static built files from `dist`, not `localhost`.

The native side owns app setup, command registration, and event emission. The bridge is meant to stay small and predictable.

## Experimental path

Future native host integration is intentionally separated. The public headers expose an experimental area for host attachment concepts, but the first release is built around standalone desktop windows instead of embedding into a larger native graphics host.
