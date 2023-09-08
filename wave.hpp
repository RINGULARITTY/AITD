#pragma once

#include "enemy.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>

class Wave {
public:
    Wave(std::vector<Enemy> enemies, std::vector<float> spawnTimes):
        started{},
        timer{},
        currentEnemy{},
        enemies{ enemies },
        spawnTimes{ spawnTimes },
        instancedEnemies{} {}

    void start(const Waypoint& startPoint) {
        for (Enemy& e : enemies) {
            e.xPos = startPoint.x;
            e.yPos = startPoint.y;
        }
        currentEnemy = 0;
        instancedEnemies.clear();
        started = true;
        timer.restart();
    }

    void debugImGUI(const Waypoint& startPoint) {
        if (ImGui::Button("Start"))
            start(startPoint);
        if (!started)
            ImGui::Text(("current_time : 0"));
        else
            ImGui::Text(("current_time : " + std::to_string(timer.getElapsedTime().asSeconds())).c_str());
        ImGui::Text(("instantiated_enemies : " + std::to_string(instancedEnemies.size())).c_str());
        ImGui::SliderInt("current_enemy", &currentEnemy, 0, static_cast<int>(enemies.size()));
        if (ImGui::TreeNode("enemies")) {
            float maxSpawnTime = *max_element(std::begin(spawnTimes), std::end(spawnTimes));
            for (int i = 0; i < enemies.size(); ++i) {
                bool isInstantiated = false;
                for (InstancedEnemy& c : instancedEnemies) {
                    if (c.getEnemy() == &enemies[i]) {
                        isInstantiated = true;
                        break;
                    }
                }
                if (ImGui::TreeNode((std::to_string(i) + (isInstantiated ? " - instantiated" : "")).c_str())) {
                    ImGui::SliderFloat("spawn_time", &spawnTimes[i], 0, maxSpawnTime);
                    enemies[i].debugImGUI();
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }

    void update(Map& map) {
        if (!started)
            return;
        for (int i = currentEnemy; i < enemies.size(); ++i) {
            if (spawnTimes[i] <= timer.getElapsedTime().asSeconds()) {
                instancedEnemies.emplace_back(&enemies[i]);
                currentEnemy++;
            }
        }

        for (int i = 0; i < instancedEnemies.size(); ++i) {
            if (!instancedEnemies[i].update(map.waypoints))
                instancedEnemies.erase(instancedEnemies.begin() + i);
        }
    }

    void render(sf::RenderWindow& w) {
        for (InstancedEnemy& c : instancedEnemies) {
            c.render(w);
        }
    }

    bool started;
    sf::Clock timer;
    
    int currentEnemy;
    std::vector<Enemy> enemies;
    std::vector<float> spawnTimes;
    std::vector<InstancedEnemy> instancedEnemies;
};