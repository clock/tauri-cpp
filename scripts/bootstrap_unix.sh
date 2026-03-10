#!/usr/bin/env bash
set -euo pipefail

missing=0

check_tool() {
  local name="$1"
  local url="$2"

  if ! command -v "$name" >/dev/null 2>&1; then
    printf 'missing: %s\ninstall: %s\n\n' "$name" "$url"
    missing=1
  fi
}

check_tool node "https://nodejs.org/"
check_tool npm "https://nodejs.org/"
check_tool cmake "https://cmake.org/download/"
check_tool cargo "https://rustup.rs/"

if [[ "$missing" -ne 0 ]]; then
  printf 'bootstrap stopped because required tools are missing\n'
  exit 1
fi

npm install
cargo fetch
cmake --preset ninja-debug

printf '\nbootstrap complete\n'
