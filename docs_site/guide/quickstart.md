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
- set a `dev_*` project as startup and press `F5`
- or run `npm run dev:plain_html`
- or run `npm run dev:vite_tailwind`
- or run `npm run dev:react_shadcn`
- or run `cmake --preset windows-debug`

## Linux and macOS

Linux and macOS stay secondary in the first release, but the repo keeps the shared layers portable.

```bash
npm run bootstrap:unix
```
