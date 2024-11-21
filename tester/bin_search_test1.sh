#!/bin/bash

echo "Assert binary search works correctly"

expected_output="Target has been found. Position: 5"
actual_output=$("../build/solution/lab1" bin-search 2 100 5 | grep -v "Execution time")

if [ "$expected_output" = "$actual_output" ]; then
    echo "Test passed: binary search works correctly."
    exit 0
else
    echo "Test failed: binary search does not work correctly."
    echo "Expected: $expected_output"
    echo "Actual: $actual_output"
    exit 1
fi