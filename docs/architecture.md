# architecture

The repo is split into four layers:

- `include/tauri_cpp` and `src` hold the public c++ api and the core runtime model
- `rust/host` holds the shared Rust side of the bridge and Tauri facing helpers
- `examples/*` hold frontend examples and thin Tauri app crates
- `docs_site` publishes the docs to GitHub Pages

The stable path is a standalone desktop app that ships static frontend files in a Tauri webview. The native side owns app setup, command registration, and event emission. The Rust layer stays thin and mostly translates between Tauri and the c++ core.

Future native host integration is intentionally separated. The public headers expose an experimental area for host attachment concepts, but the first release is built around standalone windows.
