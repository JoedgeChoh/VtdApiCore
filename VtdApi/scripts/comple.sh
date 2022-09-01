#! /bin/bash

cd ../build
rm -rf *
cmake -DVtdFramework_DOC=on \
      -DVtdApiCore_DOC=on \
      -DVtdApiCore_ENABLE_SAMPLES=on \
      ..
make install
