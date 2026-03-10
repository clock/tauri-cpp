param(
  [Parameter(Mandatory = $true)]
  [string]$ExecutablePath,
  [string]$Arguments = "",
  [int]$SettleSeconds = 5
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path $ExecutablePath)) {
  throw "executable not found: $ExecutablePath"
}

$start_time = Get-Date
$process = Start-Process -FilePath $ExecutablePath -ArgumentList $Arguments -PassThru

Start-Sleep -Seconds $SettleSeconds

$sample = Get-Process -Id $process.Id
$elapsed = (Get-Date) - $start_time

[pscustomobject]@{
  executable = $ExecutablePath
  pid = $process.Id
  startup_ms = [math]::Round($elapsed.TotalMilliseconds, 2)
  working_set_mb = [math]::Round($sample.WorkingSet64 / 1MB, 2)
  private_memory_mb = [math]::Round($sample.PrivateMemorySize64 / 1MB, 2)
} | ConvertTo-Json
