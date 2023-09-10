#include "tower.hpp"

Tower::Tower(EntityManager& em,
    ComponentManager<PositionComponent>& posManager,
    ComponentManager<DamageComponent>& dmgManager,
    ComponentManager<RangeComponent>& rngManager)
    : entityManager(em),
    positionManager(posManager),
    damageManager(dmgManager),
    rangeManager(rngManager)
{
    entity = entityManager.CreateEntity();
}

void Tower::InitializeTower() {
    InitializeComponents();
}