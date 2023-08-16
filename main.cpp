#include "imgui.h"
#include "imgui-SFML.h"
#include "gameController.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "AITD");
    window.setFramerateLimit(30);

    ImGui::SFML::Init(window);

    GameController gc(
        std::vector<Ground> {{
            Ground(Ground::Type::START, sf::Vector2f(1, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(1, 2)),
            Ground(Ground::Type::WAY, sf::Vector2f(2, 2)),
            Ground(Ground::Type::WAY, sf::Vector2f(3, 2)),
            Ground(Ground::Type::WAY, sf::Vector2f(3, 1)),
            Ground(Ground::Type::WAY, sf::Vector2f(3, 0)),
            Ground(Ground::Type::WAY, sf::Vector2f(4, 0)),
            Ground(Ground::Type::WAY, sf::Vector2f(5, 0)),
            Ground(Ground::Type::END, sf::Vector2f(5, 1))
        }},
        std::vector<Wave> {{
            Wave(
                std::vector<Enemy> {{
                    Enemy(100, 1, 1),
                    Enemy(115, 1, 1)
                }},
                
                std::vector<float> {{
                    1.5,
                    2.5
                }}
            )
        }}
    );

    int a = 10, b = 20;

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