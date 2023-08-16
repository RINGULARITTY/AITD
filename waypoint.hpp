#pragma once

#include "ground.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Waypoint {
public:
    Waypoint(int& x, int& y):
        x{ x },
        y{ y },
        renderElement(5) {
        renderElement.setOrigin(sf::Vector2f(5, 5));
        renderElement.setFillColor(sf::Color(255, 150, 0, 200));
    }

    void debugImGUI() {
        ImGui::SliderInt("x", &x, 0, 20);
        ImGui::SliderInt("y", &y, 0, 10);
    }

    void render(sf::RenderWindow& w) {
        renderElement.setPosition(Ground::size * x + Ground::size / 2, Ground::size * y + Ground::size / 2);
        w.draw(renderElement);
    }

    int& x;
    int& y;
    sf::CircleShape renderElement;
};