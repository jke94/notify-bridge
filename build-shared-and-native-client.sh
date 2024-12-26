#!/bin/bash

# Variables
LIB_DIR="cpp/notify-bridge-lib"
SAMPLE_DIR="cpp/notify-bridge-sample"
BUILD_DIR="build"
LIB_NAME="libnotify_bridge.so"
EXECUTABLE_NAME="notify_bridge_sample"

# Crear directorio de compilación
mkdir -p $BUILD_DIR

# Compilar la librería compartida
echo "Compilando la librería compartida..."

g++ -shared                         \
    -fPIC                           \
    $LIB_DIR/src/*.cpp              \
    -I$LIB_DIR/include              \
    -I$LIB_DIR/api                  \
    -o $BUILD_DIR/$LIB_NAME

if [ $? -ne 0 ]; then
    echo "Error al compilar la librería compartida."
    exit 1
fi

# Compilar el ejecutable
echo "Compilando el ejecutable..."
g++ $SAMPLE_DIR/main.cpp            \
    -I$LIB_DIR/include              \
    -I$LIB_DIR/api                  \
    -L$BUILD_DIR                    \
    -lnotify_bridge                 \
    -Wl,-rpath,$(pwd)/$BUILD_DIR    \
    -o $BUILD_DIR/$EXECUTABLE_NAME

if [ $? -ne 0 ]; then
    echo "Error al compilar el ejecutable."
    exit 1
fi

# Mensaje de éxito
echo "Compilación exitosa. Ejecutable generado en $BUILD_DIR/$EXECUTABLE_NAME."
