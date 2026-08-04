#!/bin/bash

pushd ../
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++
popd
