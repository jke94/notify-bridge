#!/bin/bash

# Variables
LIB_DIR="cpp/notify-bridge-lib"
SAMPLE_DIR="cpp/notify-bridge-sample"
BUILD_DIR="build"
LIB_NAME="libnotify_bridge.so"
EXECUTABLE_NAME="notify_bridge_sample"

# A. Create compilation output directory.
mkdir -p $BUILD_DIR

# B. Building shared library.
echo "Building shared library..."

g++ -shared                         \
    -fPIC                           \
    $LIB_DIR/src/*.cpp              \
    $LIB_DIR/src/logger/*.cpp       \
    -I$LIB_DIR/api                  \
    -I$LIB_DIR/include              \
    -I$LIB_DIR/include/logger       \
    -o $BUILD_DIR/$LIB_NAME

if [ $? -ne 0 ]; then
    echo "Error compiling shared library!"
    exit 1
fi

# C. Building executable as client and linking library.
echo "Building executable client and linking library..."

g++ $SAMPLE_DIR/main.cpp            \
    -I$LIB_DIR/include              \
    -I$LIB_DIR/api                  \
    -L$BUILD_DIR                    \
    -lnotify_bridge                 \
    -Wl,-rpath,$(pwd)/$BUILD_DIR    \
    -o $BUILD_DIR/$EXECUTABLE_NAME

if [ $? -ne 0 ]; then
    echo "Error compiling executable!"
    exit 1
fi

echo "Compilation successful. Executable generated in $BUILD_DIR/$EXECUTABLE_NAME"


# D. Build and publish dotnet console app.
dotnet publish \
    ./dotnet/NotifyBridge.ConsoleApp/NotifyBridge.ConsoleApp.csproj \
    -c Release \
    -r linux-x64 \
    -p:PublishSingleFile=true \
    --self-contained true \
    --output ./publish/NotifyBridge.ConsoleApp

# D. Copy native shared library to dotnet publish folder.
cp $BUILD_DIR/$LIB_NAME ./publish/NotifyBridge.ConsoleApp