# unix setup

Linux and macOS stay secondary in the first release. The repo keeps the shared layers portable, but Windows is still the first-class setup and validation path.

## Prerequisites

- Node.js 20 or newer
- CMake 3.30 or newer
- Rust with `rustup`
- the platform Tauri prerequisites for your OS

## First run

```bash
npm run bootstrap:unix
```

After that, use the `ninja-debug` preset or your own preferred generator.

## Current expectation

Use this path when you are validating portability or preparing later Linux and macOS support. For the smoothest onboarding and the primary examples workflow, use the [Windows quickstart](/guide/quickstart).
