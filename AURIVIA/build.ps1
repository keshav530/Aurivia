#!/usr/bin/env pwsh
# AURIVIA Engine Build Script

param(
    [string]$Configuration = "Release",
    [switch]$Clean = $false,
    [switch]$BuildTests = $false,
    [switch]$RunDemo = $false
)

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$buildDir = Join-Path $projectRoot "build"

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  AURIVIA Engine Build Script" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

# Clean if requested
if ($Clean) {
    Write-Host "`nCleaning build directory..." -ForegroundColor Yellow
    if (Test-Path $buildDir) {
        Remove-Item $buildDir -Recurse -Force
    }
}

# Create build directory
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# Configure
Write-Host "`nConfiguring CMake..." -ForegroundColor Yellow
Push-Location $buildDir
cmake .. -G "Visual Studio 17 2022"

# Build
Write-Host "`nBuilding engine ($Configuration)..." -ForegroundColor Yellow
cmake --build . --config $Configuration

# Check build status
if ($LASTEXITCODE -eq 0) {
    Write-Host "`n✓ Build successful!" -ForegroundColor Green
} else {
    Write-Host "`n✗ Build failed!" -ForegroundColor Red
    Pop-Location
    exit 1
}

Pop-Location

# Run demo if requested
if ($RunDemo) {
    Write-Host "`nLaunching demo..." -ForegroundColor Yellow
    $demoExe = Join-Path $buildDir "bin\$Configuration\cube_demo.exe"
    if (Test-Path $demoExe) {
        & $demoExe
    } else {
        Write-Host "Demo executable not found: $demoExe" -ForegroundColor Red
    }
}

Write-Host "`nBuild complete!" -ForegroundColor Green
