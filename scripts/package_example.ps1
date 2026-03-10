param(
  [Parameter(Mandatory = $true)]
  [string]$ExampleName
)

$ErrorActionPreference = "Stop"

$cargo_bin = Join-Path $env:USERPROFILE ".cargo\bin"
if (Test-Path $cargo_bin) {
  $env:Path = "$cargo_bin;$env:Path"
}

$example_dir = Join-Path $PSScriptRoot "..\examples\$ExampleName"

if (-not (Test-Path $example_dir)) {
  throw "example not found: $ExampleName"
}

Push-Location $example_dir

try {
  npm exec -- tauri build
} finally {
  Pop-Location
}
