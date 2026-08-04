#!/bin/bash

pushd ../Sample
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++
popd
