@echo off

pushd "%~dp0..\Docs"
doxygen Doxyfile

pushd "%~dp0..\Sample"
cmake -S . -B build -G "Visual Studio 18 2026"
popd
pause