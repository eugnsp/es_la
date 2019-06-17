#!/bin/sh

make clean
cd ../doxygen
doxygen
#cp -r images/* xml
cd ../sphinx
make html
