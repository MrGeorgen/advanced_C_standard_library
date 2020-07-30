#!/bin/sh
rm -rf build
cmake .
make
./acl
