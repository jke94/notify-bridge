#!/bin/bash

mkdir -p lib

g++ -fPIC                                   \
    -shared                                 \
    -I./cpp/notify-bridge-lib/api           \
    -I./cpp/notify-bridge-lib/include       \
    ./cpp/notify-bridge-lib/src/*.cpp       \
    -o ./lib/notify-bridge-lib.so    