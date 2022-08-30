#!/bin/bash

source variables.sh

${FFPLAY} \
    -fflags nobuffer \
    rtsp://localhost:8554/vtd.rtp
