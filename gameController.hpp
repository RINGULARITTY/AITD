#pragma once

#include "map.hpp"
#include "wave.hpp"

class GameController {
public:
    GameController(const std::vector<Ground>& grounds, const std::vector<Wave>& waves):
        currentWave{},
        waves{ waves },
        map(grounds) {}

    void start() {
        waves[currentWave].start();
    }

    void update() {
        waves[currentWave].update();
    }


    void debugImGUI() {
        if (ImGui::TreeNode("map")) {
            map.debugImGUI();
            ImGui::TreePop();
        }

        if (ImGui::TreeNode(("waves (" + std::to_string(waves.size()) + ")").c_str())) {
            ImGui::SliderInt("current_wave", &currentWave, 0, waves.size());
            for (int i = 0; i < waves.size(); ++i) {
                if (ImGui::TreeNode(std::to_string(i).c_str())) {
                    waves[currentWave].debugImGUI();
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
};