# tauri-cpp agent notes

## Project

This repo is a Windows-first starter library for building desktop gui applications in c++ with Tauri. The stable target is standalone desktop apps. Native host attachment for directx, opengl, or other frameworks is future work and stays experimental until the standalone path is solid.

## Priorities

- easy setup for outside users
- low memory use and low bridge overhead
- Visual Studio friendly on Windows
- portable enough that Linux and macOS are not painful later

## Working rules

- keep code style plain and direct
- use snake_case in c++ code
- use c++20
- use smart pointers only
- use proper ownership and avoid raw owning pointers
- keep comments rare
- when comments are needed, keep them lower case
- one line `if` statements do not get braces
- keep public APIs small and obvious

## Scope

- stable: standalone desktop app flow
- experimental: native host integration beyond the Tauri shell

## Repo habits

- keep `CHECKLIST.md` current when work lands
- prefer Windows docs and validation first
- do not add handoff junk or generated sounding filler docs
- keep markdown short and useful
