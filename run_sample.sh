#!/bin/bash

# Check if a sample name was provided
if [ -z "$1" ]; then
    echo "Error: No sample name provided."
    echo "Usage: ./run_sample.sh <sample_name>"
    exit 1
fi

# Run the command with the provided argument
./build/linux/app/bin/Release/x86_64/vulkan_samples sample "$1"
