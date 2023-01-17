#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "World.hpp"
#include "Lib.hpp"
#include "Entities.hpp"
#include "CmdFile.hpp"
#include "imgui.h"
enum class Direction : int {
	right,
	left,
	up,
	down
};
enum class State : int {
	menu,
	inGame,
	gameOver
};
using namespace sf;
Body* snakeHead;
Body* snakeTail;
Apple* apple;
Direction direction;
State state;
void Play() {
	srand(time(NULL));
	sf::ContextSettings settings(0, 0, 2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Game");
	window.setFramerateLimit(18);
	window.setVerticalSyncEnabled(true);
	time_t lastModificationTime = {};
	double frameStart = 0;
	double frameEnd = 0.05f;
	for (int y = 0; y < Game::CELL_Y - 2; y++) {
		for (int x = 0; x < Game::CELL_X; x++) {
			world.cells.push_back(new Cell(Vector2i(x, y),
				new RectangleShape(Vector2f(Game::CELL_SIZE, Game::CELL_SIZE)),
				(x + y) % 2 == 0 ? sf::Color::Color(153, 153, 153, 5) : sf::Color::Color(153, 153, 153, 20)));
		}
	}
	snakeHead = new Body;
	snakeHead->direction = sf::Vector2i(1, 0);
	direction = Direction::right;
	state = State::menu;
	snakeHead->gridPos.y = 3;
	snakeTail = snakeHead;
	apple = new Apple;
	apple->gridPos = apple->Pop(snakeHead);
	float timerInput = 0;
	float timerInputLimit = 0.2;
	while (window.isOpen()) {
		double dt = frameEnd - frameStart;
		timerInput -= dt;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (state == State::inGame && timerInput <= 0) {
					if (event.key.code == Keyboard::Z && direction != Direction::down) {
						snakeHead->direction = sf::Vector2i(0, -1);
						direction = Direction::up;
						timerInput = timerInputLimit;
					}
					if (event.key.code == Keyboard::Q && direction != Direction::right) {
						snakeHead->direction = sf::Vector2i(-1, 0);
						direction = Direction::left;
						timerInput = timerInputLimit;
					}
					if (event.key.code == Keyboard::S && direction != Direction::up) {
						snakeHead->direction = sf::Vector2i(0, 1);
						direction = Direction::down;
						timerInput = timerInputLimit;
					}
					if (event.key.code == Keyboard::D && direction != Direction::left) {
						snakeHead->direction = sf::Vector2i(1, 0);
						direction = Direction::right;
						timerInput = timerInputLimit;
					}
				}else if (event.key.code == Keyboard::P) {
					state = State::inGame;
				}
				if (event.key.code == Keyboard::R) {
					state = State::inGame;
					snakeHead = new Body;
					snakeHead->direction = sf::Vector2i(1, 0);
					direction = Direction::right;
					snakeHead->gridPos.y = 3;
					snakeTail = snakeHead;
					apple->gridPos = apple->Pop(snakeHead);
				}
			}
		}
		window.clear();
		world.draw(window);
		for (auto s : world.cells) {
			s->draw(window);
		}
		if (state == State::inGame) {
			snakeHead->update();
			Body* temp = snakeHead;
			while (temp) {
				temp->draw(window);
				temp = temp->nextBody;
				if (temp != nullptr && snakeHead->gridPos.x == temp->gridPos.x &&
					snakeHead->gridPos.y == temp->gridPos.y) state = State::gameOver;
			}
			if (snakeHead->gridPos.x == apple->gridPos.x &&
				snakeHead->gridPos.y == apple->gridPos.y) {
				snakeTail->nextBody = new Body;
				snakeTail = snakeTail->nextBody;
				apple->gridPos = apple->Pop(snakeHead);
			}
			apple->draw(window);
		}
		else if (state == State::gameOver) {
			Body* temp = snakeHead;
			while (temp) {
				temp->draw(window);
				temp = temp->nextBody;
			}
			apple->draw(window);
		}
		window.display();
	}
}
int main() {
	Play();
	return 0;
}