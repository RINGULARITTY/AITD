#pragma once

#include "enemy.hpp"
#include "tile.hpp"

class EndTile : public Tile {
    void OnEnter(Enemy enemy) override {
    }
};