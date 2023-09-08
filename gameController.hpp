#pragma once

#include "map.hpp"
#include "wave.hpp"

class GameController {
public:
    GameController(const std::vector<Ground>& grounds, const std::vector<Wave>& waves, sf::Int32 systemUpdateDelta) :
        currentWave{},
        waves{ waves },
        map(grounds),
        updater{},
        leftUpdate{ 0 },
        systemUpdateDelta{ systemUpdateDelta } {}

    void start() {
        waves[currentWave].start(map.waypoints[0]);
        updater.restart();
    }

    void update() {
        leftUpdate += updater.getElapsedTime().asMilliseconds();
        if (leftUpdate >= systemUpdateDelta) {
            updater.restart();
            while (leftUpdate >= systemUpdateDelta) {
                waves[currentWave].update(map);
                leftUpdate -= systemUpdateDelta;
            }
        }
    }


    void debugImGUI() {
        if (ImGui::TreeNode("map")) {
            map.debugImGUI();
            ImGui::TreePop();
        }

        if (ImGui::TreeNode(("waves (" + std::to_string(waves.size()) + ")").c_str())) {
            ImGui::SliderInt("current_wave", &currentWave, 0, static_cast<int>(waves.size()));
            for (int i = 0; i < waves.size(); ++i) {
                if (ImGui::TreeNode(std::to_string(i).c_str())) {
                    waves[currentWave].debugImGUI(map.waypoints[0]);
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }

    void render(sf::RenderWindow& w) {
        map.render(w);
        waves[currentWave].render(w);
    }

    int currentWave;
    std::vector<Wave> waves;
    Map map;
    sf::Clock updater;
    sf::Int32 leftUpdate;
    sf::Int32 systemUpdateDelta;
};