#pragma once

#include <functional>
#include <SFML/Graphics/RectangleShape.hpp>

struct PositionComponent {
    float x, y;
};

struct DamageComponent {
    float baseDamage;
    float CalculateDamage(int level) { return 0; }
};

struct RangeComponent {
    float baseRange;
    float CalculateRange(int level) { return 0; }
};

struct LevelComponent {
    int level;
};

struct TowerRenderComponent {
    sf::RectangleShape rectangle;
};

struct ConstitutionComponent {
    float currentHp;
    std::function<float(int)> MaxHp;
    std::function<float(int)> Defense;

    void InitCurrentHp(const LevelComponent& levelComponent) {
        currentHp = MaxHp(levelComponent.level);
    }

    void ApplyDamage(float damage, int level) {
        float actualDamage = damage - Defense(level);
        if (actualDamage < 0) actualDamage = 0;
        currentHp -= actualDamage;
        if (currentHp < 0) currentHp = 0;
    }
};

struct SwimComponent {
    float speed;
};