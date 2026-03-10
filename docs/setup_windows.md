# windows setup

## required tools

- Visual Studio 2022 with Desktop development with C++
- Node.js 20+
- CMake 3.30+
- Rust with `rustup`
- WebView2 runtime

## first run

```powershell
npm run bootstrap:windows
```

This script checks the machine, tells you exactly what is missing, installs npm dependencies, fetches Cargo dependencies, and configures the default CMake preset.

## common tasks

```powershell
cmake --preset windows-debug
cmake --build --preset windows-debug
ctest --preset windows-debug
```

Open `vs/tauri_cpp.sln` if you want the Visual Studio entry point for bootstrap, build, test, and package tasks.

## f5 flow

Open `vs/tauri_cpp.sln`, set one of these as the startup project, then press `F5`:

- `dev_plain_html`
- `dev_vite_tailwind`
- `dev_react_shadcn`

What happens:

- missing npm dependencies are installed
- the selected example is prepared with a one shot build when you build the project
- `F5` launches `tauri dev`
- frontend changes are watched by the example dev server
- Rust changes rebuild through Cargo

## terminal dev flow

```powershell
npm run dev:plain_html
npm run dev:vite_tailwind
npm run dev:react_shadcn
```

Do not use raw `cargo run` for the Vite based debug apps. They point at a local dev server in debug mode, so `cargo run` by itself will open a blank or refused page if that dev server is not running.

## rust note

If `cargo` works in `cmd.exe` but not in PowerShell, prepend the local cargo bin path in the shell you are using:

```powershell
$env:Path = "$env:USERPROFILE\.cargo\bin;$env:Path"
```

## smoke tests

```powershell
$env:Path = "$env:USERPROFILE\.cargo\bin;$env:Path"
cargo run -p tauri_cpp_plain_html -- --smoke-test
cargo run -p tauri_cpp_vite_tailwind -- --smoke-test
cargo run -p tauri_cpp_react_shadcn -- --smoke-test
```
