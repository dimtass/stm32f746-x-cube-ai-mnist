#!/bin/bash -e

OUTPUT_F="./source/src/inc/"

echo "Creating framebuffer C header..."
flatcc -a -o ./source/schema/ ./source/schema/schema.fbs

echo "Copying generated header files to ${OUTPUT_F}..."
cp ./source/schema/*.h ./${OUTPUT_F}/