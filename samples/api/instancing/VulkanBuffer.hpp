// this entire file is written by Gemini 3 Thinking
// i think the idea is to make a wrapper class so that we dont have to manually call the instancing destructors in that example.
#pragma once
#define VK_NO_PROTOTYPES // what does it mean the macro is redefined? is that bad?
#include "volk.h"
#include <stdexcept>

class VulkanBuffer {
public:
    VulkanBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) 
        : device(device) {
        
        // 1. Create the Buffer handle
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO; // REQUIRED
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &bufferHandle) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }

        // 2. Get memory requirements
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, bufferHandle, &memRequirements);

        // 3. Setup Allocation Info
        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO; // REQUIRED
        allocInfo.allocationSize = memRequirements.size;
        // You must find the right memory type index (see below)
        allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &memoryHandle) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }

        vkBindBufferMemory(device, bufferHandle, memoryHandle, 0);
    }

    ~VulkanBuffer() {
        if (bufferHandle != VK_NULL_HANDLE) vkDestroyBuffer(device, bufferHandle, nullptr);
        if (memoryHandle != VK_NULL_HANDLE) vkFreeMemory(device, memoryHandle, nullptr);
    }

    VkBuffer getHandle() const { return bufferHandle; }

private:
    VkDevice device;
    VkBuffer bufferHandle = VK_NULL_HANDLE;
    VkDeviceMemory memoryHandle = VK_NULL_HANDLE;

    // Helper to find the right memory "drawer" on your GPU
    uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }
        throw std::runtime_error("failed to find suitable memory type!");
    }
};
