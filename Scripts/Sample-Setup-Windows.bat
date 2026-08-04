@echo off

pushd ..\Sample
cmake -S . -B build -G "Visual Studio 18 2026"
popd
pause
