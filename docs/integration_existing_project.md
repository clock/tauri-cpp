# integrate into an existing project

The lowest friction path right now is to treat one of the example apps as the shell around your existing code instead of trying to rewrite your current build all at once.

## standalone app path

1. Pick the example closest to what you want:
   - `plain_html` for the lightest setup
   - `vite_tailwind` for regular Tailwind
   - `react_shadcn` for a component based frontend
2. Copy your frontend into that example.
3. Put your native work behind the command handlers in `examples/<example>/src-tauri/src/lib.rs`.
4. If the command should call into c++, wire it through `rust/host/cpp/demo_bridge.cpp`.
5. Rename the app identifier and window title in `src-tauri/tauri.conf.json`.
6. Press `F5` on the matching `dev_*` Visual Studio project.

## existing c++ codebase path

If you already have c++ code:

1. Keep your existing code in its current library or move it under `src/` and `include/tauri_cpp`.
2. Add a narrow command surface from Rust into c++ instead of exposing your whole engine to the webview.
3. Return small json payloads over the bridge.
4. Keep heavy work native side and only send status or result summaries to the frontend.

## current note

The shared c++ api is in place, but the direct `app_builder::run` path is not the main integration route yet. The easiest working route today is:

- frontend in an example app
- Tauri commands in `src-tauri/src/lib.rs`
- c++ logic behind the `rust/host` bridge
