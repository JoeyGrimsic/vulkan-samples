#include <cstdint>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

// The "Entity" is just an ID (a handle)
using Entity = uint32_t;

// --- 1. The Components (Plain Old Data / POD) ---
// These must be tightly packed so they can be copied directly to VRAM
struct Position {
    float x, y, z;
};

struct Velocity {
    float vx, vy, vz;
};

// --- 2. The Component Pool ---
// This acts as the "Class of Arrays" for a specific type
class IComponentPool {
public:
    virtual ~IComponentPool() = default;
};

template<typename T>
class ComponentPool : public IComponentPool {
public:
    std::vector<T> data; // The contiguous array for the GPU!
    
    // Maps Entity ID to the index in the 'data' vector
    std::unordered_map<Entity, size_t> entityToIndex;

    void add(Entity entity, T component) {
        entityToIndex[entity] = data.size();
        data.push_back(component);
    }
};

// --- 3. The Registry (The "System" Manager) ---
class Registry {
private:
    Entity nextEntity = 0;
    std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> pools;

public:
    Entity createEntity() {
        return nextEntity++;
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        auto type = std::type_index(typeid(T));
        if (pools.find(type) == pools.end()) {
            pools[type] = std::make_unique<ComponentPool<T>>();
        }
        static_cast<ComponentPool<T>*>(pools[type].get())->add(entity, component);
    }

    template<typename T>
    ComponentPool<T>* getPool() {
        return static_cast<ComponentPool<T>*>(pools[std::type_index(typeid(T))].get());
    }
};
