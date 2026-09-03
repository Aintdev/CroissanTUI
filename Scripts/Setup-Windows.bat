@echo off

set "RED=[31m"
set "GREEN=[32m"
set "RESET=[0m"

:: ============================
:: Check Doxygen
:: ============================

where doxygen >nul 2>&1

if not errorlevel 1 (
    set "DOXYGEN_PATH=doxygen"
    goto :doxygen
)

:: Doxygen not in PATH - search installation directory
for /f "delims=" %%D in ('where.exe /R "%ProgramFiles%" doxygen.exe 2^>nul') do (
    set "DOXYGEN_PATH=%%D"
)

if defined DOXYGEN_PATH goto :doxygen

echo %RED%ERROR: Doxygen not found!%RESET%
echo.

where winget >nul 2>&1

if errorlevel 1 goto :doxygen_no_winget

:: ============================
:: Doxygen missing + winget
:: ============================

echo Continue without Doxygen [Y]
echo Cancel Setup             [N]
echo Install Doxygen (winget) [I]

choice /C YNI /N /M "[Y/N/I]: "

if errorlevel 3 goto :install_doxygen
if errorlevel 2 goto :cancel
goto :cmake

:: ============================
:: Doxygen missing + no winget
:: ============================

:doxygen_no_winget

echo Continue without Doxygen        [Y]
echo Cancel Setup                   [N]
echo %RED%Install Doxygen (winget)   [I] UNAVAILABLE%RESET%

choice /C YN /N /M "[Y/N]: "

if errorlevel 2 goto :cancel
goto :cmake

:: ============================
:: Run Doxygen
:: ============================

:doxygen

echo %GREEN%Running Doxygen...%RESET%

pushd "%~dp0..\Docs"

"%DOXYGEN_PATH%" Doxyfile

if errorlevel 1 (
    popd
    echo %RED%ERROR: Doxygen failed!%RESET%
    goto :cmake
)

popd

:: ============================
:: Check CMake
:: ============================

:cmake

where cmake >nul 2>&1

if errorlevel 1 (
    echo %RED%ERROR: CMake not found!%RESET%
    goto :error
)

:: ============================
:: Run CMake
:: ============================

echo %GREEN%Running CMake...%RESET%

pushd "%~dp0.."

cmake -S . -B build -G "Visual Studio 18 2026"

if errorlevel 1 (
    popd
    echo %RED%ERROR: CMake configuration failed!%RESET%
    goto :error
)

popd

echo.
echo %GREEN%CMake configuration successful!%RESET%

pause
goto :eof

:: ============================
:: Install Doxygen
:: ============================

:install_doxygen

echo.
echo Installing Doxygen via winget...

winget install --id DimitriVanHeesch.Doxygen -e

if errorlevel 1 (
    echo %RED%ERROR: Failed to install Doxygen!%RESET%
    goto :error
)

echo %GREEN%Doxygen installed successfully!%RESET%
echo.

:: Find freshly installed Doxygen
for /f "delims=" %%D in ('where.exe /R "%ProgramFiles%" doxygen.exe 2^>nul') do (
    set "DOXYGEN_PATH=%%D"
)

if defined DOXYGEN_PATH goto :doxygen

echo %RED%ERROR: Doxygen installed but executable could not be found!%RESET%
echo Possible Solution:
echo Restart the shell and run this setup script again.
goto :error

:: ============================
:: Error
:: ============================

:error

echo.
timeout /t 5 /nobreak >nul
goto :eof

:: ============================
:: Cancel
:: ============================

:cancel

echo.
echo Canceled.
timeout /t 5 /nobreak >nul
goto :eof