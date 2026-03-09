#!/bin/bash

INPUT_DIR="./maps/good"
OUTPUT_DIR="./valgrind_outputs"
PROGRAM="./cub3D"   # çalıştırmak istediğin program

mkdir -p "$OUTPUT_DIR"

for testfile in "$INPUT_DIR"/*; do
    if [ -f "$testfile" ]; then
        filename=$(basename "$testfile")
        outputfile="$OUTPUT_DIR/${filename}.log"

        echo "Running $filename ..."

        valgrind --leak-check=full \
                 --show-leak-kinds=all \
                 --track-origins=yes \
                 "$PROGRAM" "$testfile" \
                 > "$outputfile" 2>&1
    fi
done

echo "All tests finished."