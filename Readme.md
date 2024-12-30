[![Build and Publish](https://github.com/jke94/notify-bridge/actions/workflows/build-shared-library-and-publish-dotnet-app.yml/badge.svg)](https://github.com/jke94/notify-bridge/actions/workflows/build-shared-library-and-publish-dotnet-app.yml)

# notify-bridge

Proof of concept about how works C# (.NET) with C++ under an observer pattern implementation in the native code. Consuming native bussiness logic through native shared library that is consumed from C# using P/Invoke.

This example also contains a excelent example about how to consume a native logs coming from shared library and exported to the client through C++ native callback. And finally, designed a custom logger provider to log messages from C# and C++ native callback using the power of .NET framework to extend customizations.

## How to build.

### 1. Native code (C++): Shared library and client.

Simple native client to consume shared library.

- Linux:

```
./build-shared-library-and-native-client.sh
```

### 2. .NET console app with C++: Console client consuming shared library.

Simple .NET console client that consume library bussiness logic: **cpp/notify-bridge-lib/api/NotifyBridgeApi.h**

```
./build-shared-library-and-publish-dotnet-app.sh 
```

## Setup environment requirements to build example.

The example have been developed with the following tool versions:

| Tool/Framework | Version | 
| :---   | :--- |
| .NET | 8.0.111 |
| g++ | g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0 |

## Useful information.

- [Marshalling Data with Platform Invoke](https://learn.microsoft.com/en-us/dotnet/framework/interop/marshalling-data-with-platform-invoke)