# unix setup

Linux and macOS are supported as follow-on targets. The repo keeps the shared code portable, but Windows is still the first class path for setup and validation.

## required tools

- Node.js 20+
- CMake 3.30+
- Rust with `rustup`
- the platform Tauri prerequisites for your OS

## first run

```bash
npm run bootstrap:unix
```

Then use the `ninja-debug` preset or your own preferred generator.
