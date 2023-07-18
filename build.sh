#!/bin/sh

LAYER_TARGET=

cmake -DLAYER_TARGET=${LAYER_TARGET} -DLIBRARY_SHARED=ON -DCMAKE_BUILD_TYPE=debug -B build
cmake --build build
