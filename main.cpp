#include "imgui.h"
#include "imgui-SFML.h"
#include "gameController.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "AITD");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    GameController gc(
        std::vector<Ground> {{
            Ground(Ground::Type::START, sf::Vector2f(1, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(1, 2)),
            Ground(Ground::Type::WAY, sf::Vector2f(2, 2)),
            Ground(Ground::Type::WAY, sf::Vector2f(3, 2)),
            Ground(Ground::Type::WAY, sf::Vector2f(3, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(4, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(5, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(6, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(7, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(8, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(9, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(10, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(11, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(12, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(13, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(14, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(15, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(16, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(17, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(18, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(18, 2)),
            Ground(Ground::Type::WAY, sf::Vector2f(18, 3)),
            Ground(Ground::Type::WAY, sf::Vector2f(18, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(17, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(16, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(15, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(14, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(13, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(12, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(11, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(10, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(9, 4)),
            Ground(Ground::Type::WAY, sf::Vector2f(9, 5)),
            Ground(Ground::Type::WAY, sf::Vector2f(9, 6)),
            Ground(Ground::Type::WAY, sf::Vector2f(9, 7)),
            Ground(Ground::Type::WAY, sf::Vector2f(9, 8)),
            Ground(Ground::Type::WAY, sf::Vector2f(9, 9)),
            Ground(Ground::Type::WAY, sf::Vector2f(8, 9)),
            Ground(Ground::Type::WAY, sf::Vector2f(7, 9)),
            Ground(Ground::Type::WAY, sf::Vector2f(7, 8)),
            Ground(Ground::Type::WAY, sf::Vector2f(7, 7)),
            Ground(Ground::Type::WAY, sf::Vector2f(7, 6)),
            Ground(Ground::Type::WAY, sf::Vector2f(7, 5)),
            Ground(Ground::Type::WAY, sf::Vector2f(6, 5)),
            Ground(Ground::Type::WAY, sf::Vector2f(5, 5)),
            Ground(Ground::Type::WAY, sf::Vector2f(5, 4)),
            Ground(Ground::Type::END, sf::Vector2f(4, 4)),

            Ground(Ground::Type::TOWER, sf::Vector2f(2, 1)),
        }},
        std::vector<Wave> {{
            Wave(
                std::vector<Enemy> {{
                    Enemy(100, 1),
                    Enemy(115, 1)
                }},
                
                std::vector<float> {{
                    1.5,
                    2.5
                }}
            )
        }},
        15
    );

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        gc.update();

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(1600 - 600 - 5, 5));
        ImGui::SetNextWindowSize(ImVec2(600, 900 - 10));

        ImGui::Begin("Settings");

        if (ImGui::TreeNode("game_controller")) {
            gc.debugImGUI();
            ImGui::TreePop();
        }

        ImGui::End();

        window.clear();
        gc.render(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}