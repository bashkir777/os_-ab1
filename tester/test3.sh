#!/bin/bash

echo "Assert built-in command 'ls' works correctly"

expected_output=$(ls)
actual_output=$("../build/solution/shell" 1 ls)

if [ "$expected_output" = "$actual_output" ]; then
    echo "Test passed: 'ls' works correctly."
else
    echo "Test failed: 'ls' does not work correctly."
    echo "Expected: $expected_output"
    echo "Actual: $actual_output"
fi
