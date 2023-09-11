#pragma once

#include "enemy.hpp"

class FishmanEnemy : public Enemy {
protected:
    ComponentManager<SwimComponent>& swimManager;

public:
    FishmanEnemy(EntityManager& entityManager,
        ComponentManager<PositionComponent>& positionManager,
        ComponentManager<LevelComponent>& levelManager,
        ComponentManager<ConstitutionComponent>& constitutionManager,
        ComponentManager<SwimComponent>& swimManager):
        Enemy(entityManager, positionManager, levelManager, constitutionManager), swimManager{ swimManager } {}

    void InitializeComponents() override {
        positionManager.AddComponent(entity, PositionComponent{ 0, 0 });
        levelManager.AddComponent(entity, LevelComponent{ 1 });
        
        constitutionManager.AddComponent(entity, ConstitutionComponent{ 
            0,
            [](int level) -> float { return 100 + 20 * static_cast<float>(level); },
            [](int level) -> float { return 5 + 3.5 * static_cast<float>(level); }
        });
        constitutionManager.GetComponent(entity).InitCurrentHp(levelManager.GetComponent(entity));

        swimManager.AddComponent(entity, SwimComponent{ 1 });
    }
};