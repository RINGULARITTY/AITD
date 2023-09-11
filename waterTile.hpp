#pragma once

#include "enemy.hpp"
#include "pathTile.hpp"

class WaterTile : public PathTile {
    void OnEnter(Enemy enemy) override {
        // logique pour une tuile d'eau
        if (enemy.CanSwim()) {
            // permettre le passage
        }
        else {
            // bloquer le passage
        }
    }
};