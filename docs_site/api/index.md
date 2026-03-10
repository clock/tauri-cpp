# api overview

The public c++ surface is small on purpose.

## Headers

- `app_builder.hpp`
- `window_options.hpp`
- `frontend_config.hpp`
- `command_context.hpp`
- `event_bus.hpp`

## Main types

- `window_options` sets size, visibility, and window basics
- `frontend_config` points to static frontend assets
- `command_request` and `command_response` are the simple command bridge types
- `event_bus` lets native code publish small event payloads
- `app_builder` owns app setup and command registration

## Current note

The repo already has the shared Rust bridge and example app wiring. The fully native `app_builder::run` path is still being finished so the public c++ api can launch the Tauri host directly with less glue.
