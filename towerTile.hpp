#pragma once

#include "enemy.hpp"
#include "tile.hpp"

class TowerTile : public Tile {
    void OnEnter(Enemy enemy) override {
        // peut-�tre bloquer le passage ou infliger des d�g�ts
    }
};