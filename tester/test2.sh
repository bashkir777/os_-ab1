#!/bin/bash

echo "Assert built-in command 'echo' works correctly"

expected_output="string"
actual_output=$("../build/solution/shell" 1 echo "string")

if [ "$expected_output" = "$actual_output" ]; then
    echo "Test passed: 'echo' works correctly."
else
    echo "Test failed: 'echo' does not work correctly."
    echo "Expected: $expected_output"
    echo "Actual: $actual_output"
fi