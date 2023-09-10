#pragma once

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