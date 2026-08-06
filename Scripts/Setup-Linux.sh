#!/bin/bash

pushd ../
cmake -S . -B build -G "Unix Makefiles"
popd
