#!/bin/sh

CLANG_FORMAT=clang-format-9
find ./include -type f \( -iname "*.hpp" -or -iname "*.cpp" \) | xargs $CLANG_FORMAT -style=file -i
find ./src -type f \( -iname "*.hpp" -or -iname "*.cpp" \) | xargs $CLANG_FORMAT -style=file -i
