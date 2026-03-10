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
$example_dir = Join-Path $root_dir "examples\$ExampleName"

if (-not (Test-Path $example_dir)) {
  throw "example not found: $ExampleName"
}

if (-not (Get-Command node -ErrorAction SilentlyContinue)) {
  throw "node not found on path"
}

if (-not (Get-Command npm -ErrorAction SilentlyContinue)) {
  throw "npm not found on path"
}

if (-not (Get-Command cargo -ErrorAction SilentlyContinue)) {
  throw "cargo not found on path"
}

if (-not (Test-Path (Join-Path $root_dir "node_modules"))) {
  Push-Location $root_dir
  try {
    npm install
  } finally {
    Pop-Location
  }
}

Push-Location $root_dir

try {
  switch ($ExampleName) {
    "plain_html" { npm run build:plain_html }
    "vite_tailwind" { npm run build:vite_tailwind }
    "react_shadcn" { npm run build:react_shadcn }
    default { throw "unsupported example: $ExampleName" }
  }

  switch ($ExampleName) {
    "plain_html" { cargo check -p tauri_cpp_plain_html }
    "vite_tailwind" { cargo check -p tauri_cpp_vite_tailwind }
    "react_shadcn" { cargo check -p tauri_cpp_react_shadcn }
  }
} finally {
  Pop-Location
}
