#!/bin/sh
rm -rf build
cmake .
make
./build/test.out
