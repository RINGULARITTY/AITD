#include "entityManager.hpp"

EntityManager::EntityManager() : nextEntityID{ 0 }, activeEntities {} {}

Entity EntityManager::CreateEntity() {
    Entity newEntity = nextEntityID;
    activeEntities.insert(newEntity);
    nextEntityID++;
    return newEntity;
}

void EntityManager::DestroyEntity(Entity entity) {
    activeEntities.erase(entity);

    for (auto& manager : componentManagers) {
        manager->RemoveComponent(entity);
    }
}

void EntityManager::RegisterComponentManager(ComponentManagerBase* manager) {
    componentManagers.push_back(manager);
}