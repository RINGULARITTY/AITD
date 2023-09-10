#pragma once

#include "componentManager.hpp"
#include "components.hpp"
#include "entityManager.hpp"

class Tower {
protected:
    Entity entity;

    EntityManager& entityManager;
    ComponentManager<PositionComponent>& positionManager;
    ComponentManager<DamageComponent>& damageManager;
    ComponentManager<RangeComponent>& rangeManager;

public:
    Tower(EntityManager& entityManager,
        ComponentManager<PositionComponent>& positionManager,
        ComponentManager<DamageComponent>& damageManager,
        ComponentManager<RangeComponent>& rangeManager);

    void InitializeTower();
    virtual void InitializeComponents() = 0;
};
