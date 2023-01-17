#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Game.hpp"

class Entity {
public:
	sf::Shape* shp = nullptr;
	sf::Vector2i gridPos = sf::Vector2i(0, 0);
	sf::Vector2i direction = sf::Vector2i(0, 0);

	Entity() {}
	Entity(sf::Vector2f pixelPos, sf::Shape* shp);

	void setPixelPos(sf::Vector2f npos);
	void setGridPos(sf::Vector2f npos);

	void im();

	inline auto getLocalBounds() const {
		return shp->getLocalBounds();
	};
	inline auto getGlobalBounds() const {
		return shp->getGlobalBounds();
	};
	inline auto getPosition() const {
		return shp->getPosition();
	};
	inline void setPosition(const sf::Vector2f& v) {
		shp->setPosition(v);
	};
	void syncGridToPixel();
	void draw(sf::RenderWindow& win);
	bool collides(float gx, float gy);
};

class Body : public Entity {
public:
	sf::Vector2i lastPos;
	Body* nextBody = nullptr;
	Body() {
		shp = new sf::RectangleShape(sf::Vector2f(Game::CELL_SIZE, Game::CELL_SIZE));
		shp->setFillColor(sf::Color::Green);

	}
	void Move(sf::Vector2i pos);
	void update();
};

class Apple : public Entity {
public:
	Apple() {
		shp = new sf::CircleShape(Game::CELL_SIZE / 2);
		shp->setFillColor(sf::Color::Red);
	}
	sf::Vector2i Pop(Body* snake);
};

class Cell : public Entity {
public:
	Cell(sf::Vector2i pos, sf::Shape* shape, const sf::Color color) {
		shp = shape;
		shp->setFillColor(color);
		shp->setPosition(sf::Vector2f(pos.x * Game::CELL_SIZE, pos.y * Game::CELL_SIZE + Game::CELL_SIZE * 2));
	}
};
