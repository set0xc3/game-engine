<h1 align="center">GameEngine</h1>

```sheel
export LAYER_TARGET=runtime

cmake \
-DLAYER_TARGET=$LAYER_TARGET \
-DLIBRARY_SHARED=ON \
-DCMAKE_BUILD_TYPE=debug \
-B build && cmake --build build

cmake --build build --target run-$LAYER_TARGET
```

```sheel
cmake \
    -DCMAKE_SYSTEM_NAME=Windows \
    -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc \
    -DCMAKE_CXX_COMPILER=i686-w64-mingw32-g++ \
    -DLAYER_TARGET=$LAYER_TARGET \
    -DLIBRARY_SHARED=ON \
    -DCMAKE_BUILD_TYPE=debug \
    -DCMAKE_PREFIX_PATH=build \
    -B build && cmake --build build

cmake --build build --target run-$LAYER_TARGET
```
