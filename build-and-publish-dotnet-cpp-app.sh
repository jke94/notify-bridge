#!/bin/bash

# A. Create output folder for shared library.
mkdir -p lib

# B. Compile and generate shared library.
g++ -fPIC                                   \
    -shared                                 \
    -I./cpp/notify-bridge-lib/api           \
    -I./cpp/notify-bridge-lib/include       \
    ./cpp/notify-bridge-lib/src/*.cpp       \
    -o ./lib/notify-bridge-lib.so    

# C. Build and publish dotnet console app.
dotnet publish \
    ./dotnet/NotifyBridge.ConsoleApp/NotifyBridge.ConsoleApp.csproj \
    -c Release \
    -r linux-x64 \
    -p:PublishSingleFile=true \
    --self-contained true \
    --output ./publish/NotifyBridge.ConsoleApp

# D. Copy native shared library to dotnet publish folder.
cp ./lib/notify-bridge-lib.so ./publish/NotifyBridge.ConsoleApp