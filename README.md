# tauri-cpp

`tauri-cpp` is a Windows-first starter for building small desktop gui apps in c++ with a Tauri shell. The main path is standalone desktop apps. The repo also leaves room for later directx, opengl, or other host integration without turning the first release into a pile of build tooling.

## What is in here

- a small c++ api under `include/tauri_cpp`
- a shared Rust host crate using `cxx`
- three frontend examples
- bootstrap scripts for Windows first, unix second
- a committed Visual Studio solution for common tasks
- docs in the repo and a VitePress site for GitHub Pages

## Current focus

- keep setup obvious for Windows users
- keep the runtime light
- keep the public c++ layer small enough to understand
- keep cross platform work possible later without rewriting the repo

## Quick start

1. Install Visual Studio 2022 with Desktop development with C++.
2. Install Node.js 20 or newer.
3. Install CMake 3.30 or newer.
4. Install Rust with `rustup`.
5. Make sure WebView2 runtime is present.
6. Run `npm run bootstrap:windows`.

After that:

- open `vs/tauri_cpp.sln` in Visual Studio
- set `dev_plain_html`, `dev_vite_tailwind`, or `dev_react_shadcn` as the startup project
- press `F5`
- or use `cmake --preset windows-debug`
- or use `npm run dev:plain_html`, `npm run dev:vite_tailwind`, or `npm run dev:react_shadcn`

`F5` on a `dev_*` project runs a watched `tauri dev` session. Frontend changes reload through the dev server, and Rust changes rebuild through Cargo.

## Run and test

Build the frontend assets:

```powershell
npm run build:plain_html
npm run build:vite_tailwind
npm run build:react_shadcn
```

Build and test the c++ core:

```powershell
cmake --preset windows-debug
cmake --build --preset windows-debug
ctest --preset windows-debug
```

Check the Rust and Tauri crates:

```powershell
$env:Path = "$env:USERPROFILE\.cargo\bin;$env:Path"
cargo test -p tauri_cpp_host --no-run
cargo check -p tauri_cpp_plain_html
cargo check -p tauri_cpp_vite_tailwind
cargo check -p tauri_cpp_react_shadcn
```

Run the smoke tests:

```powershell
$env:Path = "$env:USERPROFILE\.cargo\bin;$env:Path"
cargo run -p tauri_cpp_plain_html -- --smoke-test
cargo run -p tauri_cpp_vite_tailwind -- --smoke-test
cargo run -p tauri_cpp_react_shadcn -- --smoke-test
```

Package an app:

```powershell
npm run package:plain_html
```

## important dev note

Do not use raw `cargo run` for the Vite based debug apps. In debug they use a dev server URL, so use one of these instead:

```powershell
npm run dev:plain_html
npm run dev:vite_tailwind
npm run dev:react_shadcn
```

If you want to run without a dev server, use the release runner:

```powershell
npm run run:plain_html
npm run run:vite_tailwind
npm run run:react_shadcn
```

## Examples

- `examples/plain_html` is the default low overhead starter
- `examples/vite_tailwind` shows a regular Vite + Tailwind setup
- `examples/react_shadcn` shows a React + shadcn/ui setup

## Docs

- repo docs live in `docs/`
- GitHub Pages at `https://clock.github.io/tauri-cpp/` is the primary public docs surface
- the GitHub Pages site is built from `docs_site/`
- existing project integration notes are in `docs/integration_existing_project.md`

## Status

Check `CHECKLIST.md` for current progress and the next recommended task.
