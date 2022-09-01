#! /bin/bash

cd ../build
rm -rf *
cmake -DVtdFramework_DOC=on ..
make install
