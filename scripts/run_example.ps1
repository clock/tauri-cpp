param(
  [Parameter(Mandatory = $true)]
  [string]$ExampleName
)

$ErrorActionPreference = "Stop"

$cargo_bin = Join-Path $env:USERPROFILE ".cargo\bin"
if (Test-Path $cargo_bin) {
  $env:Path = "$cargo_bin;$env:Path"
}

$root_dir = Resolve-Path (Join-Path $PSScriptRoot "..")

Push-Location $root_dir

try {
  switch ($ExampleName) {
    "plain_html" {
      npm run build:plain_html
      cargo run --release -p tauri_cpp_plain_html
    }
    "vite_tailwind" {
      npm run build:vite_tailwind
      cargo run --release -p tauri_cpp_vite_tailwind
    }
    "react_shadcn" {
      npm run build:react_shadcn
      cargo run --release -p tauri_cpp_react_shadcn
    }
    default {
      throw "unsupported example: $ExampleName"
    }
  }
} finally {
  Pop-Location
}
