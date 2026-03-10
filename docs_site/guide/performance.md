# performance

This repo is meant to stay lean.

## Rules

- one webview by default
- no background Node process in production
- small IPC payloads
- shared native work stays in c++ instead of bouncing large data through JavaScript

## Targets

- plain html under 90 MB idle rss
- vite tailwind under 105 MB idle rss
- react shadcn under 125 MB idle rss

Use `scripts/measure_windows.ps1` after packaging an example app.
