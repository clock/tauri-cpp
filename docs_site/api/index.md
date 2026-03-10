# api overview

The public C++ surface is small on purpose. The goal is to keep the stable API obvious instead of exposing a large abstraction layer too early.

## Headers

- `app_builder.hpp`
- `window_options.hpp`
- `frontend_config.hpp`
- `command_context.hpp`
- `event_bus.hpp`

## Main types

- `window_options` sets size, visibility, and core window behavior
- `frontend_config` points to packaged frontend assets
- `command_request` and `command_response` keep the command bridge simple
- `event_bus` lets native code publish small event payloads
- `app_builder` owns app setup and command registration

## Current note

The repo already has the shared Rust bridge and example app wiring. The fully native `app_builder::run` path is still being finished so the public C++ API can launch the Tauri host directly with less glue.

Until that lands, the practical route is still:

- frontend in an example app
- Tauri commands in the example crate
- native logic behind the `rust/host` bridge

The actual control path is:

`frontend -> Rust command -> rust/host bridge -> C++`

The main native files in that path today are:

- `src/app_builder.cpp`
- `src/event_bus.cpp`
- `rust/host/cpp/demo_bridge.cpp`
