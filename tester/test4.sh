#!/bin/bash

echo "Assert built-in command 'ls' with args '-la' works correctly"

expected_output=$(ls -la)
actual_output=$("../build/solution/shell" 1 ls -la)

if [ "$expected_output" = "$actual_output" ]; then
    echo "Test passed: 'ls -la' works correctly."
else
    echo "Test failed: 'ls -la' does not work correctly."
    echo "Expected: $expected_output"
    echo "Actual: $actual_output"
fi
