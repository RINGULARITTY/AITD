#pragma once

#include "system.hpp"
#include "componentManager.hpp"
#include "components.hpp"
#include <SFML/Graphics.hpp>

class TowerRenderSystem : public System {
private:
    ComponentManager<PositionComponent>& positionManager;
    ComponentManager<TowerRenderComponent>& renderManager;
    sf::RenderWindow& window;

public:
    TowerRenderSystem(ComponentManager<PositionComponent>& posManager,
        ComponentManager<TowerRenderComponent>& rendManager,
        sf::RenderWindow& win)
        : positionManager(posManager), renderManager(rendManager), window(win) {}

    void UpdateRender() override {
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
            if (positionManager.HasComponent(entity) && renderManager.HasComponent(entity)) {
                sf::RectangleShape& rectangle = renderManager.GetComponent(entity).rectangle;
                PositionComponent& position = positionManager.GetComponent(entity);

                rectangle.setPosition(position.x, position.y);
            }
        }
    }

    void Render() override {
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
            if (renderManager.HasComponent(entity)) {
                window.draw(renderManager.GetComponent(entity).rectangle);
            }
        }
    }
};