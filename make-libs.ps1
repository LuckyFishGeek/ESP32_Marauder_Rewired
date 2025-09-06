# make-libs.ps1
# Creates ./lib and downloads all required libraries into it

$LibRoot = Join-Path (Get-Location) 'lib'
New-Item -Path $LibRoot -ItemType Directory -Force | Out-Null

function Clone-Repo {
    param(
        [Parameter(Mandatory)][string]$Repo,   # e.g. "marian-craciunescu/ESP32Ping"
        [Parameter(Mandatory)][string]$Ref,    # e.g. "1.6" or "v2.0.6" or "master"
        [Parameter(Mandatory)][string]$Dest    # folder name under ./lib
    )
    $destPath = Join-Path $LibRoot $Dest
    if (Test-Path $destPath) { Remove-Item -Recurse -Force $destPath }
    git clone --branch $Ref --depth 1 "https://github.com/$Repo.git" $destPath
    Write-Host "? $Repo@$Ref -> $destPath"
}

Write-Host "Using lib folder: $LibRoot"

# --- GitHub-sourced libs (pinned) ---
Clone-Repo "marian-craciunescu/ESP32Ping"       "1.6"       "ESP32Ping"
Clone-Repo "me-no-dev/AsyncTCP"                 "master"    "AsyncTCP"
Clone-Repo "stevemarple/MicroNMEA"              "v2.0.6"    "MicroNMEA"
Clone-Repo "Bodmer/TFT_eSPI"                    "V2.5.34"   "TFT_eSPI"
Clone-Repo "PaulStoffregen/XPT2046_Touchscreen" "v1.4"      "XPT2046_Touchscreen"
Clone-Repo "h2zero/NimBLE-Arduino"              "1.3.8"     "NimBLE-Arduino"

# Prefer your custom ESPAsyncWebServer if present at ./Custom/ESPAsyncWebServer
$customEAS = Join-Path (Get-Location) "Custom/ESPAsyncWebServer"
$easDest   = Join-Path $LibRoot "ESPAsyncWebServer"
if (Test-Path $customEAS) {
    if (Test-Path $easDest) { Remove-Item -Recurse -Force $easDest }
    Copy-Item -Recurse -Force $customEAS $easDest
    Write-Host "? Custom ESPAsyncWebServer copied -> $easDest"
} else {
    Write-Warning "Custom/ESPAsyncWebServer not found. (Skipped; add it later if needed.)"
}

# --- ?Registry? libs pulled from their GitHub sources at pinned versions ---
Clone-Repo "bblanchon/ArduinoJson"              "v6.18.2"   "ArduinoJson"
Clone-Repo "adafruit/Adafruit_NeoPixel"         "1.10.7"    "Adafruit_NeoPixel"
Clone-Repo "ivanseidel/LinkedList"              "v1.3.3"    "LinkedList"
Clone-Repo "plerup/espsoftwareserial"           "8.1.0"     "EspSoftwareSerial"
Clone-Repo "adafruit/Adafruit_BusIO"            "1.15.0"    "Adafruit_BusIO"
Clone-Repo "adafruit/Adafruit_MAX1704X"         "1.0.2"     "Adafruit_MAX1704X"

Write-Host "`nAll libraries downloaded into: $LibRoot"