#pragma once

#include "tower.hpp"

class ArcherTower : public Tower {
public:
    ArcherTower(EntityManager& entityManager,
        ComponentManager<PositionComponent>& positionManager,
        ComponentManager<DamageComponent>& damageManager,
        ComponentManager<RangeComponent>& rangeManager);

    void InitializeComponents() override;
};