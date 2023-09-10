#pragma once

#include "entityManager.hpp"
#include <array>

template <typename T>
class ComponentManager : public ComponentManagerBase {
private:
    std::array<T, MAX_ENTITIES> componentArray;
    std::array<bool, MAX_ENTITIES> entityHasComponent;

public:
    void AddComponent(Entity entity, T component) {
        componentArray[entity] = component;
        entityHasComponent[entity] = true;
    }

    void RemoveComponent(Entity entity) override {
        entityHasComponent[entity] = false;
    }

    T& GetComponent(Entity entity) {
        return componentArray[entity];
    }

    bool HasComponent(Entity entity) const override {
        return entityHasComponent[entity];
    }
};
