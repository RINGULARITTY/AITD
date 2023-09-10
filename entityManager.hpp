#pragma once

#include "entity.hpp"
#include "componentManagerBase.hpp"

#include <set>
#include <vector>

class EntityManager {
private:
    Entity nextEntityID;
    std::set<Entity> activeEntities;

    std::vector<ComponentManagerBase*> componentManagers;

public:
    EntityManager();

    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    void RegisterComponentManager(ComponentManagerBase* manager);
};