# existing projects

The simplest current path is not a deep framework integration. Start from one example app and put your existing native logic behind the Rust bridge.

## use an example as the shell

1. pick `plain_html`, `vite_tailwind`, or `react_shadcn`
2. move your frontend into that example
3. expose a small command surface in `src-tauri/src/lib.rs`
4. forward the native work into c++ through `rust/host/cpp/demo_bridge.cpp`
5. press `F5` from the matching `dev_*` Visual Studio project

## keep the bridge small

- keep heavy work in c++
- send small json payloads to the frontend
- add commands one by one instead of trying to mirror your entire native api
