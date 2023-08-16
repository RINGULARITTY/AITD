#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Ground {
public:
	static float size;
	static sf::Color colors[5];

	enum class Type {
		GROUND = 0,
		TOWER = 1,
		WAY = 2,
		START = 3,
		END = 4
	};

	Ground(const Ground::Type& type, const sf::Vector2f& pos) :
		type{ type },
		renderElement(sf::Vector2f(size, size)),
		xPos{ static_cast<int>(pos.x) },
		yPos{ static_cast<int>(pos.y) } {

		renderElement.setFillColor(colors[static_cast<int>(type)]);
		renderElement.setPosition(size * pos);
	}

	void debugImGUI() {
		ImGui::SliderInt("x", &xPos, 0, 20);
		ImGui::SliderInt("y", &yPos, 0, 10);
	}

	void render(sf::RenderWindow& w) {
		renderElement.setPosition(size * static_cast<float>(xPos), size * static_cast<float>(yPos));
		renderElement.setSize(sf::Vector2f(size, size));
		w.draw(renderElement);
	}

	Ground::Type type;
	int xPos, yPos;
	sf::RectangleShape renderElement;
};

float Ground::size{ 35 };
sf::Color Ground::colors[5] = { sf::Color::Yellow, sf::Color::Blue, sf::Color::White, sf::Color::Green, sf::Color::Red };