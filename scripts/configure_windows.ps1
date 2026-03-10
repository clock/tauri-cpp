$ErrorActionPreference = "Stop"
$root_dir = Resolve-Path (Join-Path $PSScriptRoot "..")
Push-Location $root_dir
try {
  cmake --preset windows-debug
  if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
  }
} finally {
  Pop-Location
}
