#!/bin/sh

cmake -DBUILD_TARGET=editor -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=debug -B build
cmake --build build
