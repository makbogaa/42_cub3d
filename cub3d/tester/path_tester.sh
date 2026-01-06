#!/bin/bash

# Tester script for cub3d
# Usage: ./tester.sh

MAP_DIR="/home/mdalkili/map"
MAPS=("invalid_map1.cub" "test1.cub" "invalid_map2.cub" "test2.cub", ".test2.cub", ".test1.cub")

# Her map için test et
for map in "${MAPS[@]}"; do
    echo "Testing $map..."
     ../cub3d "../$MAP_DIR/$map"
    EXIT_CODE=$?
    if [ $EXIT_CODE -eq 0 ]; then
        echo "✓ $map: Passed"
    else
        echo "✗ $map: Failed (Exit code: $EXIT_CODE)"
    fi
    echo "---"
done

echo "Testing 2 completed.\n"