#!/bin/bash

# Variables.
EXECUTABLE="./build/notify_bridge_sample"
FILE_OUTPUT_NAME="valgrind-out.txt"

valgrind --leak-check=full              \
         --show-leak-kinds=all          \
         --track-origins=yes            \
         --verbose                      \
         --log-file=$FILE_OUTPUT_NAME   \
         $EXECUTABLE
