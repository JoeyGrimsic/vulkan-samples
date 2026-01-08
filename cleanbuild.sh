#!/usr/bin/env bash
set -e

# Added -DVKB_SAMPLES_TO_BUILD="hello_triangle_1_3"
cmake -G "Unix Makefiles" -Bbuild/linux \
  -DCMAKE_BUILD_TYPE=Release \
  -DVKB_WSI_SELECTION=WAYLAND \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DVKB_SAMPLES_TO_BUILD="hello_triangle_1_3;instancing" 

# Then build as normal
cmake --build build/linux --config Release --target vulkan_samples -j$(nproc)
./build/linux/app/bin/Release/x86_64/vulkan_samples sample hello_triangle_1_3
