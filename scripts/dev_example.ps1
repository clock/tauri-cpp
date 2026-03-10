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

if (-not (Test-Path (Join-Path $root_dir "node_modules"))) {
  Push-Location $root_dir
  try {
    npm install
  } finally {
    Pop-Location
  }
}

Push-Location $example_dir

try {
  npm exec -- tauri dev
} finally {
  Pop-Location
}
