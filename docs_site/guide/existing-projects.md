# existing projects

The least painful current path is not a deep framework integration. Start from one example app, use it as the shell, and put your existing native logic behind the Rust bridge.

## Use an example as the shell

1. pick `plain_html`, `vite_tailwind`, or `react_shadcn`
2. move your frontend into that example
3. expose a small command surface in `src-tauri/src/lib.rs`
4. forward the native work into c++ through `rust/host/cpp/demo_bridge.cpp`
5. press `F5` from the matching `dev_*` Visual Studio project

This is the preferred integration path because it keeps the moving pieces small and avoids rewriting your whole build up front.

## Existing c++ codebase path

If you already have c++ code:

1. keep the existing library where it is or move it under `src/` and `include/tauri_cpp`
2. expose a narrow Rust command surface instead of mirroring the full native API
3. return small json payloads to the frontend
4. keep heavy work native side and send summaries, not large data blobs

## Keep the bridge small

- keep heavy work in c++
- send small json payloads to the frontend
- add commands one by one instead of trying to mirror your entire native api

The intended control path is:

`frontend -> Rust command -> rust/host bridge -> C++`

## Current note

The shared C++ API is in place, but the direct `app_builder::run` path is not the main integration route yet. The easiest working route today is:

- frontend in an example app
- Tauri commands in `src-tauri/src/lib.rs`
- c++ logic behind the `rust/host` bridge
