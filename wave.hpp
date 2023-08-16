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
        renderEnemies{} {}

    void start() {
        currentEnemy = 0;
        renderEnemies.clear();
        started = true;
        timer.restart();
    }

    void debugImGUI() {
        if (ImGui::Button("Start"))
            start();
        if (!started)
            ImGui::Text(("current_time : 0"));
        else
            ImGui::Text(("current_time : " + std::to_string(timer.getElapsedTime().asSeconds())).c_str());
        ImGui::Text(("instantiated_enemies : " + std::to_string(renderEnemies.size())).c_str());
        ImGui::SliderInt("current_enemy", &currentEnemy, 0, enemies.size());
        if (ImGui::TreeNode("enemies")) {
            float maxSpawnTime = *max_element(std::begin(spawnTimes), std::end(spawnTimes));
            for (int i = 0; i < enemies.size(); ++i) {
                bool isInstantiated = false;
                for (CircleEnemy& c : renderEnemies) {
                    if (&c.enemy == &enemies[i]) {
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

    void update() {
        if (!started)
            return;
        for (int i = currentEnemy; i < enemies.size(); ++i) {
            if (spawnTimes[i] <= timer.getElapsedTime().asSeconds()) {
                renderEnemies.push_back(CircleEnemy(enemies[i]));
                currentEnemy++;
            }
        }

        // TODO : Wrapper CircleEnemy dans une classe avec son vecteur direction et l'id du waypoint pour le faire bouger
    }

    void render(sf::RenderWindow& w) {
        for (CircleEnemy& c : renderEnemies) {
            c.render(w);
        }
    }

    bool started;
    sf::Clock timer;
    
    int currentEnemy;
    std::vector<Enemy> enemies;
    std::vector<float> spawnTimes;
    std::vector<CircleEnemy> renderEnemies;
};