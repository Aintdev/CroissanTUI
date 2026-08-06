@echo off

pushd "%~dp0.."
cmake -S . -B build -G "Visual Studio 18 2026"
popd
pause