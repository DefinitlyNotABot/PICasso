#!/usr/bin/env bash

# Usage: ./analyze_cpp.sh

SEARCH_DIRS=(./src ./header)

# Verify directories exist
EXISTING_DIRS=()
for d in "${SEARCH_DIRS[@]}"; do
    [ -d "$d" ] && EXISTING_DIRS+=("$d")
done

if [ ${#EXISTING_DIRS[@]} -eq 0 ]; then
    echo "No src/ or header/ directories found."
    exit 1
fi

# Collect .cpp and .hpp files
mapfile -d '' ALL_FILES < <(
    find "${EXISTING_DIRS[@]}" -type f \( \
        -name "*.cpp" -o \
        -name "*.hpp" \
    \) -print0
)

if [ ${#ALL_FILES[@]} -eq 0 ]; then
    echo "No C++ files found."
    exit 1
fi

# Count total lines of code
TOTAL_LINES=$(wc -l "${ALL_FILES[@]}" | awk 'END {print $1}')

# Count number of .hpp files as class count
mapfile -d '' HPP_FILES < <(
    find "${EXISTING_DIRS[@]}" -type f -name "*.hpp" -print0
)

CLASS_COUNT=${#HPP_FILES[@]}

echo "C++ Project Analysis"
echo "---------------------"
echo "Total lines of code: $TOTAL_LINES"
echo "Number of classes (.hpp files): $CLASS_COUNT"
