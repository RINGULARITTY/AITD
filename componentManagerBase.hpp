#pragma once

#include "entity.hpp"

class ComponentManagerBase {
public:
    virtual ~ComponentManagerBase() = default;

    virtual void RemoveComponent(Entity entity) = 0;
    virtual bool HasComponent(Entity entity) const = 0;
};
