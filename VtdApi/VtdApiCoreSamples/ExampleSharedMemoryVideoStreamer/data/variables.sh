#!/bin/bash

set -e

if [ -z ${FFMPEG_ROOT+x} ]; then
    echo "FFMPEG_ROOT is unset";
    exit 1
else 
    echo "FFMPEG_ROOT is set to '$FFMPEG_ROOT'";
fi

if [ -z ${VTD_ROOT+x} ]; then
    echo "VTD_ROOT is unset";
    exit 1
else 
    echo "VTD_ROOT is set to '$VTD_ROOT'";
fi

FFSERVER=${FFMPEG_ROOT}/bin/ffserver
FFMPEG=${FFMPEG_ROOT}/bin/ffmpeg
FFPLAY=${FFMPEG_ROOT}/bin/ffplay

export LD_LIBRARY_PATH=${VTD_ROOT}/Runtime/Core/IG64/lib:${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
