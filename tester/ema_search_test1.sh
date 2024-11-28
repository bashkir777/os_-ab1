#!/bin/bash

echo "Assert ema-search-int benchmark generates array of proper size"

../build/solution/lab1 ema-search-int 2 100 array 5 >> /dev/null
output_code=$?

if [ "$output_code" -ne 0 ]; then
    echo "Test failed: ema-search-int benchmark finished with an error."
    exit $output_code
fi

if [ ! -f "array" ]; then
    echo "Test failed: File 'array' was not created."
    exit 1
fi

expected_size=400
actual_size=$(stat -c%s "array")
if [ "$actual_size" -ne "$expected_size" ]; then
    echo "Test failed: File 'array' size is incorrect."
    echo "Expected: $expected_size bytes, Actual: $actual_size bytes."
    exit 1
fi

echo "Test passed: ema-search-int benchmark generated a file of correct size."

rm array
exit 0
