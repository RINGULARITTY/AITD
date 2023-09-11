#pragma once

#include "enemy.hpp"
#include "tile.hpp"

class SpawnTile : public Tile {
    void OnEnter(Enemy enemy) override {
        // logique pour le spawn d'un ennemi
    }
};