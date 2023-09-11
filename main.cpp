#include "imgui.h"
#include "imgui-SFML.h"

#include "systemManager.hpp"
#include "entityManager.hpp"
#include "componentManager.hpp"
#include "components.hpp"
#include "archerTower.hpp"
#include "towerRenderSystem.hpp"
#include "fishmanEnemy.hpp"


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::Uint32 SYSTEM_FPS = 30;
    sf::Uint32 left_update_time = 0;

    EntityManager entityManager;
    ComponentManager<PositionComponent> positionComponentManager;
    ComponentManager<LevelComponent> levelComponentManager;
    ComponentManager<DamageComponent> damageComponentManager;
    ComponentManager<RangeComponent> rangeComponentManager;
    ComponentManager<TowerRenderComponent> renderComponentManager;
    ComponentManager<ConstitutionComponent> constitutionComponentManager;
    ComponentManager<SwimComponent> swimComponentManger;

    ArcherTower archerTower(entityManager, positionComponentManager, damageComponentManager, rangeComponentManager);
    archerTower.InitializeTower();

    FishmanEnemy fishmanEnemy(entityManager, positionComponentManager, levelComponentManager, constitutionComponentManager, swimComponentManger);
    fishmanEnemy.InitializeComponents();

    sf::RenderWindow window(sf::VideoMode(1600, 900), "AITD");
    window.setFramerateLimit(60);

    SystemManager systemManager;
    systemManager.AddSystem<TowerRenderSystem>(positionComponentManager, renderComponentManager, window);

    sf::Clock clock;

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Uint32 timeElapsed = clock.getElapsedTime().asMilliseconds();
        if (timeElapsed + left_update_time >= 1000 / SYSTEM_FPS) {
            clock.restart();
            left_update_time += timeElapsed;
            while (left_update_time >= 1000 / SYSTEM_FPS) {
                systemManager.UpdateSystems();
                left_update_time -= 1000 / SYSTEM_FPS;
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(1600 - 600 - 5, 5));
        ImGui::SetNextWindowSize(ImVec2(600, 900 - 10));

        ImGui::Begin("Settings");

        if (ImGui::TreeNode("game_controller")) {
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("interactions")) {
            ImGui::TreePop();
        }

        ImGui::End();

        window.clear();
        systemManager.UpdateRenders();
        systemManager.Renders();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}