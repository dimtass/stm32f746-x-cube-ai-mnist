#!/bin/bash -e

OUTPUT_H="mnist_schema_generated.h"
OUTPUT_F="./source/src/inc/"

echo "Creating framebuffer C++ header..."
flatc -o ./source/schema/ --cpp ./source/schema/schema.fbs

echo "Copying ${OUTPUT_H} to ${OUTPUT_F}..."
mv ./source/schema/schema_generated.h ./${OUTPUT_F}/${OUTPUT_H}
