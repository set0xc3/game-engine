#ld.sh!/bin/sh

cmake -DLAYER_TARGET=editor -DLIBRARY_SHARED=OFF -DCMAKE_BUILD_TYPE=debug -B build
cmake --build build
