param(
  [switch]$SkipNpmInstall,
  [switch]$SkipCargoFetch,
  [switch]$SkipCmake
)

$ErrorActionPreference = "Stop"

$cargo_bin = Join-Path $env:USERPROFILE ".cargo\bin"
if (Test-Path $cargo_bin) {
  $env:Path = "$cargo_bin;$env:Path"
}

function Test-Command {
  param([string]$Name)
  return $null -ne (Get-Command $Name -ErrorAction SilentlyContinue)
}

function Write-MissingTool {
  param(
    [string]$Label,
    [string]$Url
  )

  Write-Host ""
  Write-Host "missing: $Label"
  Write-Host "install: $Url"
}

$missing = @()

if (-not (Test-Command "node")) {
  $missing += "node"
  Write-MissingTool "Node.js 20+" "https://nodejs.org/"
}

if (-not (Test-Command "npm")) {
  $missing += "npm"
  Write-MissingTool "npm" "https://nodejs.org/"
}

if (-not (Test-Command "cmake")) {
  $missing += "cmake"
  Write-MissingTool "CMake 3.30+" "https://cmake.org/download/"
}

if (-not (Test-Command "cargo")) {
  $missing += "cargo"
  Write-MissingTool "Rust with rustup" "https://rustup.rs/"
}

$vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) {
  $missing += "vswhere"
  Write-MissingTool "Visual Studio 2022" "https://visualstudio.microsoft.com/vs/"
} else {
  $vs = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -format json | ConvertFrom-Json
  if (-not $vs) {
    $missing += "visual_studio"
    Write-MissingTool "Visual Studio 2022 with Desktop development with C++" "https://visualstudio.microsoft.com/vs/"
  }
}

$webview_paths = @(
  "HKLM:\SOFTWARE\WOW6432Node\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}",
  "HKLM:\SOFTWARE\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}"
)

$has_webview = $false
foreach ($path in $webview_paths) {
  if (Test-Path $path) {
    $has_webview = $true
    break
  }
}

if (-not $has_webview) {
  $missing += "webview2"
  Write-MissingTool "WebView2 runtime" "https://developer.microsoft.com/microsoft-edge/webview2/"
}

if ($missing.Count -gt 0) {
  Write-Host ""
  Write-Host "bootstrap stopped because required tools are missing"
  exit 1
}

if (-not $SkipNpmInstall) {
  npm install
}

if (-not $SkipCargoFetch) {
  cargo fetch
}

if (-not $SkipCmake) {
  cmake --preset windows-debug
}

Write-Host ""
Write-Host "bootstrap complete"
