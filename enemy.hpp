#pragma once

#include "imgui.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ground.hpp"

class Enemy {
public:
    Enemy(float health, float xPos, float yPos):
        currentHealth { health },
        health{ health },
        xPos{ xPos },
        yPos{ yPos } {}

    void debugImGUI() {
        ImGui::SliderFloat("pv", &currentHealth, 0, health);
        ImGui::SliderFloat("x", &xPos, 0, 20);
        ImGui::SliderFloat("y", &yPos, 0, 10);
    }

    float currentHealth, health;
    float xPos, yPos;
};

///////////////////////////////////////////////////////

class RenderEnemy {
public:
    RenderEnemy(const Enemy& enemy) :
        enemy{ enemy } {}

    void render(sf::RenderWindow& w) {}

    const Enemy& enemy;
};

class CircleEnemy : public RenderEnemy {
public:
    CircleEnemy(const Enemy& enemy):
        RenderEnemy(enemy),
        renderElement{} {
        renderElement.setFillColor(sf::Color::Yellow);
        renderElement.setRadius(10);
        renderElement.setOrigin(10, 10);
    }

    void render(sf::RenderWindow& w) {
        renderElement.setPosition(Ground::size * enemy.xPos + Ground::size / 2, Ground::size * enemy.yPos + Ground::size / 2);
        w.draw(renderElement);
    }

    sf::CircleShape renderElement;
};

class RectangleEnemy : public RenderEnemy {
public:
    RectangleEnemy(const Enemy& enemy) :
        RenderEnemy(enemy),
        renderElement{} {}

    void render(sf::RenderWindow& w) {
        renderElement.setPosition(Ground::size * enemy.xPos + Ground::size / 2, Ground::size * enemy.yPos + Ground::size / 2);
        w.draw(renderElement);
    }

    sf::RectangleShape renderElement;
};

///////////////////////////////////////////////////////

class ThePoint : public CircleEnemy {
public:
    ThePoint(const Enemy& enemy) :
        CircleEnemy(enemy) {
        renderElement.setFillColor(sf::Color::Green);
        renderElement.setRadius(10);
        renderElement.setOrigin(10, 10);
    }
};