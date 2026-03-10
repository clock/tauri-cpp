# quickstart

Use this page for the stable path: a standalone desktop app on Windows with the committed Visual Studio flow and one of the example frontends.

## Windows prerequisites

- Visual Studio 2022 with Desktop development with C++
- Node.js 20 or newer
- CMake 3.30 or newer
- Rust with `rustup`
- WebView2 runtime

## First run

```powershell
npm run bootstrap:windows
```

This checks the machine, installs npm packages, fetches Cargo dependencies, and configures the default CMake preset.

## Visual Studio F5 flow

1. Open `vs/tauri_cpp.sln`.
2. Set one of these startup projects:
   - `dev_plain_html`
   - `dev_vite_tailwind`
   - `dev_react_shadcn`
3. Press `F5`.

What that does:

- prepares the selected example
- launches `tauri dev`
- keeps frontend changes hot through the dev server
- rebuilds Rust changes through Cargo

`F5` is the intended development workflow. It is not the shipping workflow.

## Dev vs shipping

- `tauri dev` uses a local Vite server only in development
- packaged apps use static built files from `dist`, not `localhost`
- `Build Solution` should not be treated as "run everything"
- the intended run path is setting a `dev_*` startup project and pressing `F5`

## Terminal dev flow

```powershell
npm run dev:plain_html
npm run dev:vite_tailwind
npm run dev:react_shadcn
```

Do not use raw `cargo run` for the Vite-based debug apps. In debug they point at a local dev server, so `cargo run` by itself can open a blank or refused page.

`cargo run` alone is not the right debug path for the Vite-based examples. Use `F5` or the matching `npm run dev:*` command instead.

## Build and test

```powershell
cmake --preset windows-debug
cmake --build --preset windows-debug
ctest --preset windows-debug
```

## Cargo path note

If `cargo` works in `cmd.exe` but not in PowerShell, prepend the local cargo bin path:

```powershell
$env:Path = "$env:USERPROFILE\.cargo\bin;$env:Path"
```

That expands to a path like `C:\Users\<user>\.cargo\bin`.

## Smoke tests

```powershell
$env:Path = "$env:USERPROFILE\.cargo\bin;$env:Path"
cargo run -p tauri_cpp_plain_html -- --smoke-test
cargo run -p tauri_cpp_vite_tailwind -- --smoke-test
cargo run -p tauri_cpp_react_shadcn -- --smoke-test
```

If you need Linux or macOS notes, use the [unix setup](/guide/unix-setup) page. Windows remains the first-class setup and validation path.
