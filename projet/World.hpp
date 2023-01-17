 #pragma once
#include "Entities.hpp"

class World{
public:
	World();

	std::vector<sf::Vector2i>	statics;
	sf::VertexArray				staticGfx;
	bool collides(float gx, float gy);

	void draw(sf::RenderWindow& win);
	
	std::vector<Cell*> cells;
};

extern World world;
