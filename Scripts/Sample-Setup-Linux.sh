#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

pushd "$SCRIPT_DIR/../Docs"
doxygen Doxyfile

pushd "$SCRIPT_DIR/../Sample"
cmake -S . -B build -G "Unix Makefiles"
popd