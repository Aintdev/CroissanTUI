#!/bin/bash

pushd ../Sample
cmake -S . -B build -G "Unix Makefiles"
popd
