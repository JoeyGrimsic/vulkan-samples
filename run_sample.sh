#!/bin/bash

# 1. Define the list of available samples in an array
samples=(
    "hello_triangle" "hello_triangle_1_3" "dynamic_uniform_buffers"
    "texture_loading" "hdr" "instancing" "compute_nbody"
    "terrain_tessellation" "oit_linked_lists" "oit_depth_peeling"
    "dynamic_rendering" "conservative_rasterization" "fragment_shading_rate"
    "fragment_shading_rate_dynamic" "full_screen_exclusive" "calibrated_timestamps"
    "graphics_pipeline_library" "memory_budget" "mesh_shader_culling"
    "push_descriptors" "ray_queries" "ray_tracing_basic" "ray_tracing_extended"
    "ray_tracing_reflection" "timeline_semaphore" "shader_object"
    "shader_debugprintf" "synchronization_2" "buffer_device_address"
    "descriptor_indexing" "portability" "vertex_dynamic_state"
    "extended_dynamic_state2" "logic_op_dynamic_state" "patch_control_points"
    "fragment_shader_barycentric" "gshader_to_mshader" "color_write_enable"
    "dynamic_multisample_rasterization" "sparse_image" "dynamic_primitive_clipping"
    "simple_tensor_and_data_graph" "swapchain_images" "surface_rotation"
    "pipeline_cache" "descriptor_management" "constant_data" "render_passes"
    "msaa" "subpasses" "pipeline_barriers" "wait_idle" "layout_transitions"
    "specialization_constants" "command_buffer_usage" "multithreading_render_passes"
    "afbc" "16bit_storage_input_output" "16bit_arithmetic" "async_compute"
    "multi_draw_indirect" "texture_compression_comparison" "profiles"
    "hpp_compute_nbody" "hpp_dynamic_uniform_buffers" "hpp_hdr"
    "hpp_hello_triangle" "hpp_instancing" "hpp_oit_depth_peeling"
    "hpp_oit_linked_lists" "hpp_separate_image_sampler" "hpp_terrain_tessellation"
    "hpp_texture_loading" "hpp_texture_mipmap_generation" "hpp_mesh_shading"
    "hpp_push_descriptors" "hpp_pipeline_cache" "hpp_swapchain_images"
    "hpp_texture_compression_comparison" "mobile_nerf"
)

# 2. Display the menu
echo "----------------------------------------"
echo " Available Vulkan Samples"
echo "----------------------------------------"

count=1
for sample in "${samples[@]}"; do
    printf "%3d) %s\n" "$count" "$sample"
    ((count++))
done

echo "----------------------------------------"

# 3. Ask for User Input
read -p "Enter the number of the sample you want to run: " choice

# 4. Validate Input
if ! [[ "$choice" =~ ^[0-9]+$ ]]; then
    echo "Error: Please enter a valid number."
    exit 1
fi

if [ "$choice" -lt 1 ] || [ "$choice" -gt "${#samples[@]}" ]; then
    echo "Error: Number out of range."
    exit 1
fi

# 5. Retrieve Sample Name and Run
index=$((choice - 1))
selected_sample="${samples[$index]}"

echo "Launching: $selected_sample"
echo "----------------------------------------"

./build/linux/app/bin/Release/x86_64/vulkan_samples sample "$selected_sample"
