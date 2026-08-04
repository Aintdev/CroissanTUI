#!/bin/bash

pushd ../Sample
cmake -S . -B Build -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++
popd