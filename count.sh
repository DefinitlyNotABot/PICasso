#!/bin/bash

# Define paths
SRC_DIRS="./src ./header"
TEST_DIR="./tests"

# Regex for file types
CLASS_EXTS='.*\.\(cpp\|hpp\|h\|cc\)$'
LOC_EXTS='.*\.\(cpp\|hpp\)$'

echo "--- C++ Project Analysis ---"

# 1. Main Project (Only ./src and ./header)
# Check if directories exist to avoid find errors
MAIN_FILES=$(find $SRC_DIRS -type f -regex "$CLASS_EXTS" 2>/dev/null)
MAIN_LOC_FILES=$(echo "$MAIN_FILES" | grep -E "\.(cpp|hpp)$")

MAIN_CLASSES=$(echo "$MAIN_FILES" | xargs grep -w "class" 2>/dev/null | wc -l)
MAIN_LINES=$(echo "$MAIN_LOC_FILES" | xargs wc -l 2>/dev/null | tail -n 1 | awk '{print $1}')

# 2. Test Code (Only ./test, excluding json.hpp)
if [ -n "$TEST_DIR" ]; then
    # Find files, specifically excluding json.hpp
    TEST_FILES=$(find "$TEST_DIR" -type f -regex "$CLASS_EXTS" -not -name "json.hpp")
    TEST_LOC_FILES=$(echo "$TEST_FILES" | grep -E "\.(cpp|hpp)$")

    TEST_CLASSES=$(echo "$TEST_FILES" | xargs grep -w "class" 2>/dev/null | wc -l)
    TEST_LINES=$(echo "$TEST_LOC_FILES" | xargs wc -l 2>/dev/null | tail -n 1 | awk '{print $1}')
else
    TEST_CLASSES=0
    TEST_LINES=0
fi

echo "Source Code (src/header): $MAIN_CLASSES classes, ${MAIN_LINES:-0} lines (cpp/hpp)"
echo "Test Code (test):         $TEST_CLASSES classes, ${TEST_LINES:-0} lines (cpp/hpp)"