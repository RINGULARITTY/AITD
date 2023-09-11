#pragma once

#include "entity.hpp"
#include "entityManager.hpp"
#include "componentManager.hpp"
#include "components.hpp"

class Enemy {
protected:
    Entity entity;

    EntityManager& entityManager;
    ComponentManager<PositionComponent>& positionManager;
    ComponentManager<ConstitutionComponent>& constitutionManager;
    ComponentManager<LevelComponent>& levelManager;

public:
    Enemy(EntityManager& entityManager,
        ComponentManager<PositionComponent>& positionManager,
        ComponentManager<LevelComponent>& levelManager,
        ComponentManager<ConstitutionComponent>& constitutionManager):
        entityManager{ entityManager }, positionManager{ positionManager },
        constitutionManager{ constitutionManager }, levelManager { levelManager } {
        entity = entityManager.CreateEntity();
    }

    virtual void InitializeComponents() = 0;
};