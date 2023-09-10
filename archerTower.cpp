#include "archerTower.hpp"

ArcherTower::ArcherTower(EntityManager& em,
    ComponentManager<PositionComponent>& posManager,
    ComponentManager<DamageComponent>& dmgManager,
    ComponentManager<RangeComponent>& rngManager)
    : Tower(em, posManager, dmgManager, rngManager)
{}

void ArcherTower::InitializeComponents() {
    positionManager.AddComponent(entity, PositionComponent{ 0, 0 });
    damageManager.AddComponent(entity, DamageComponent{ 15 });
    rangeManager.AddComponent(entity, RangeComponent{ 10 });
}