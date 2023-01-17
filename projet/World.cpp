#include "Game.hpp"
#include "World.hpp"

World world;

World::World(){
	staticGfx.setPrimitiveType(sf::Quads);
}

bool World::collides(float gx, float gy) {
	if( gx > Game::WIDTH / Game::CELL_SIZE)
		return true;
	if (gy > ((Game::HEIGHT / Game::CELL_SIZE)-2))
		return true;
	else if (gx < 0) 
		return true;
	else if (gy < 0)
		return true;

	int cx = (int)gx;
	int cy = (int)gy;

	for(auto & s : statics)
		if (s.x == cx && s.y == cy)
			return true;

	return false;
}

void World::draw(sf::RenderWindow& win) {
	win.draw(staticGfx);
}
