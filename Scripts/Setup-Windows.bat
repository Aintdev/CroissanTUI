@echo off

pushd ..\
cmake -S . -B Build -G "Visual Studio 18 2026"
popd
pause