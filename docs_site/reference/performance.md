# performance

This repo is supposed to stay lean.

## Baseline rules

- one window by default
- one webview by default
- no background Node process in production
- no polling loops for native to frontend state
- keep IPC payloads small

## Current targets

- plain html idle rss under 90 MB
- vite tailwind idle rss under 105 MB
- react shadcn idle rss under 125 MB
- small command round trip p95 under 2 ms on the reference Windows machine

Use `scripts/measure_windows.ps1` once the Tauri examples are running.
