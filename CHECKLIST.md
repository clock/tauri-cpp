# checklist

## Backlog

- wire the c++ `app_builder::run` flow into the Rust host so a native app can launch without extra glue
- package each example through its Tauri app crate
- add a real perf harness for startup and memory checks
- add CI for CMake tests and Rust checks
- add Linux and macOS validation passes
- add experimental host integration examples

## In Progress

- wire the shared Rust host crate through a full local Tauri package pass
- tighten the standalone launch path so the public c++ api can own it directly

## Done

- created repo metadata and top level docs
- added root build manifests for CMake, Cargo workspace, and npm workspaces
- added Windows first and unix secondary bootstrap scripts
- added the docs site and GitHub Pages workflow
- added the committed Visual Studio task solution
- added the public c++ headers, native core, and unit tests
- added the shared Rust host scaffold with a `cxx` bridge
- added the plain html, vite tailwind, and react shadcn examples
- built all three frontend examples and the docs site
- configured, built, and tested the c++ target with CMake on Windows
- compiled the shared Rust host crate
- compiled all three Tauri app crates
- ran smoke-test launches for all three example apps

## Blocked

- none right now

## Next Recommended Task

Finish the shared native core, the Rust host crate, and the three example apps so the bootstrap scripts and solution can drive a working build.
