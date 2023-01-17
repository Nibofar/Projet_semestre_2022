#include "Entities.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "imgui.h"

Entity::Entity(sf::Vector2f pixelPos, sf::Shape* shp) {
	this->shp = shp;

	setPixelPos(pixelPos);
}

void Entity::setPixelPos(sf::Vector2f npos) {
	gridPos.x = (int)npos.x / Game::CELL_SIZE;
	gridPos.y = (int)npos.y / Game::CELL_SIZE;
	shp->setPosition(npos);
}

void Entity::setGridPos(sf::Vector2f npos) {
	setPixelPos(sf::Vector2f(npos.x * Game::CELL_SIZE, npos.y * Game::CELL_SIZE));
}

void Entity::im() {
	using namespace ImGui;
	DragInt2("cx", &gridPos.x);
	Value("pos x", shp->getPosition().x);
	Value("pos y", shp->getPosition().y);
}

void Entity::syncGridToPixel() {
	float pxX = (gridPos.x) * Game::CELL_SIZE;
	float pxY = (gridPos.y) * Game::CELL_SIZE;
	shp->setPosition(sf::Vector2f((int)pxX, (int)pxY));
}

void Body::update() {
	sf::Vector2i lastPos = gridPos;
	gridPos += direction;
	bool needSync = true;
	if (gridPos.x <= 0) direction.x = 0;
	else if (gridPos.x >= Game::CELL_X - 1) direction.x = 0;
	if (gridPos.y <= 2) direction.y = 0;
	else if (gridPos.y >= Game::CELL_Y - 1) direction.y = 0;
	if (needSync) syncGridToPixel();
	if(nextBody) nextBody->Move(lastPos);
}

void Body::Move(sf::Vector2i pos) {
	if (nextBody != nullptr) {
		nextBody->Move(gridPos);
	}
	shp->setPosition(sf::Vector2f(pos.x * Game::CELL_SIZE, pos.y * Game::CELL_SIZE));
	gridPos = pos;
}

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
}

bool Entity::collides(float gx, float gy) {
	return world.collides(gx, gy);
}

sf::Vector2i Apple::Pop(Body* snake) {
	bool verif = true;
	int posX = 0;
	int posY = 0;
	do{
		Body* temp = snake;
		verif = true;
		posX = rand() % Game::CELL_X;
		posY = rand() % (Game::CELL_Y - 2) + 2;
		while (temp) {
			if (temp->gridPos.x == posX && temp->gridPos.y == posY) {
				verif = false;
				break;
			}
			temp = temp->nextBody;
		}
	} while (!verif);
	shp->setPosition(sf::Vector2f(posX * Game::CELL_SIZE, posY * Game::CELL_SIZE));
	return sf::Vector2i(posX, posY);
}
