#!/bin/sh
mkdir -p build
cd build
cmake .. -DVtdFramework_USE_HDF5=ON
make
