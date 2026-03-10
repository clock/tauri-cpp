# quickstart

## Windows

Install:

- Visual Studio 2022 with Desktop development with C++
- Node.js 20 or newer
- CMake 3.30 or newer
- Rust through `rustup`
- WebView2 runtime

Run:

```powershell
npm run bootstrap:windows
```

Then either:

- open `vs/tauri_cpp.sln`
- or run `cmake --preset windows-debug`

## Linux and macOS

Linux and macOS stay secondary in the first release, but the repo keeps the shared layers portable.

```bash
npm run bootstrap:unix
```
