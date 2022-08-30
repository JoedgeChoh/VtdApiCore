#!/bin/bash

source variables.sh

./ExampleSharedMemoryVideoStreamer \
    --output-filename http://localhost:8090/vtd.ffm \
    --bitrate 7000000 \
    --pixel-format rgb0 \
    --encoder nvenc \
    --output-resolution 960 540 \
    --input-framerate 60 1 \
    --output-framerate 60 1 \
    --av-dictionary \
        preset=ll \
        g=600 \
