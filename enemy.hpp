#pragma once

#include "imgui.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ground.hpp"

class Enemy {
public:
    Enemy(float health, float speed):
        currentHealth { health },
        health{ health },
        speed{ speed },
        xPos{ 0 },
        yPos{ 0 } {}

    void debugImGUI() {
        ImGui::SliderFloat("hp", &currentHealth, 0, health);
        ImGui::SliderFloat("speed", &speed, 0.25, 4);
        ImGui::SliderFloat("x", &xPos, 0, 20);
        ImGui::SliderFloat("y", &yPos, 0, 10);
    }

    float currentHealth, health;
    float speed;
    float xPos, yPos;
};

///////////////////////////////////////////////////////

class RenderEnemy {
public:
    RenderEnemy(Enemy* enemy) :
        enemy{ enemy } {}

    virtual void render(sf::RenderWindow& w) = 0;

    Enemy* enemy;
};

class CircleEnemy : public RenderEnemy {
public:
    CircleEnemy(Enemy* enemy) :
        RenderEnemy(enemy),
        renderElement{} {
        renderElement.setFillColor(sf::Color(200, 50, 0));
        renderElement.setOutlineColor(sf::Color::Black);
        renderElement.setOutlineThickness(1);
        renderElement.setRadius(5);
        renderElement.setOrigin(10, 10);
    }

    void render(sf::RenderWindow& w) {
        renderElement.setPosition(Ground::size * enemy->xPos + Ground::size / 2, Ground::size * enemy->yPos + Ground::size / 2);
        w.draw(renderElement);
    }

    sf::CircleShape renderElement;
};


class RectangleEnemy : public RenderEnemy {
public:
    RectangleEnemy(Enemy* enemy) :
        RenderEnemy(enemy),
        renderElement{} {}

    void render(sf::RenderWindow& w) {
        renderElement.setPosition(Ground::size * enemy->xPos + Ground::size / 2, Ground::size * enemy->yPos + Ground::size / 2);
        w.draw(renderElement);
    }

    sf::RectangleShape renderElement;
};

class InstancedEnemy {
public:
    InstancedEnemy(Enemy* enemy) :
        waypointIndex{ 0 },
        renderEnemy{ enemy } {}

    Enemy* getEnemy() const {
        return renderEnemy.enemy;
    }

    const size_t& getWaypointIndex() const {
        return waypointIndex;
    }

    bool update(std::vector<Waypoint> waypoints) {
        if (renderEnemy.enemy->health <= 0)
            return false;

        Waypoint& wp = waypoints[waypointIndex];
        if (sqrt(pow(renderEnemy.enemy->xPos - wp.x, 2) + pow(renderEnemy.enemy->yPos - wp.y, 2)) <= 0.1) {
            waypointIndex++;
        }
        if (waypointIndex >= waypoints.size())
            return false;

        Waypoint& new_wp = waypoints[waypointIndex];
        float xDirection = new_wp.x - renderEnemy.enemy->xPos;
        float yDirection = new_wp.y - renderEnemy.enemy->yPos;
        float distance = sqrt(pow(xDirection, 2) + pow(yDirection, 2));
        xDirection /= distance * renderEnemy.enemy->speed; yDirection /= distance * renderEnemy.enemy->speed;
    
        renderEnemy.enemy->xPos += 0.05 * xDirection; renderEnemy.enemy->yPos += 0.05 * yDirection;

        return true;
    }

    void render(sf::RenderWindow& w) {
        renderEnemy.render(w);
    }

private:
    size_t waypointIndex;
    CircleEnemy renderEnemy;
};