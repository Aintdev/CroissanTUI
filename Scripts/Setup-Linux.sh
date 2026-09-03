#!/bin/bash

RED='\033[31m'
GREEN='\033[32m'
RESET='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# ============================
# Check Doxygen
# ============================

if ! command -v doxygen &> /dev/null; then
    echo -e "${RED}ERROR: Doxygen not found!${RESET}"
    echo
    echo "Continue without Doxygen [Y]"
    echo "Cancel Setup             [N]"
    echo

    read -r -p "[Y/N]: " choice

    case "$choice" in
        [Yy])
            echo
            echo "Continuing without Doxygen..."
            ;;
        [Nn])
            echo
            echo "Canceled."
            exit 0
            ;;
        *)
            echo
            echo "Invalid choice. Setup canceled."
            exit 1
            ;;
    esac
else
    # ============================
    # Run Doxygen
    # ============================

    echo -e "${GREEN}Running Doxygen...${RESET}"

    pushd "$SCRIPT_DIR/../Docs" > /dev/null

    if ! doxygen Doxyfile; then
        popd > /dev/null
        echo -e "${RED}ERROR: Doxygen failed!${RESET}"
    else
        popd > /dev/null
    fi
fi


# ============================
# Check CMake
# ============================

if ! command -v cmake &> /dev/null; then
    echo -e "${RED}ERROR: CMake not found!${RESET}"
    echo
    echo "Please install CMake and run this setup script again."
    exit 1
fi


# ============================
# Run CMake
# ============================

echo -e "${GREEN}Running CMake...${RESET}"

pushd "$SCRIPT_DIR/.." > /dev/null

if ! cmake -S . -B build; then
    popd > /dev/null
    echo -e "${RED}ERROR: CMake configuration failed!${RESET}"
    exit 1
fi

popd > /dev/null

echo
echo -e "${GREEN}CMake configuration successful!${RESET}"