#include "Lib.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Entities.hpp"
#include "Game.hpp"
#include "CmdFile.hpp"
#include "World.hpp"
#include "imgui.h"
#include <unordered_map>
#include <algorithm>
#include "Dijkstra.hpp"
using namespace sf;
void play() {
	sf::ContextSettings settings(0, 0, 2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Game");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	time_t lastModificationTime = {};
	double frameStart = 0;
	double frameEnd = 0.0015f;
	while (window.isOpen()) {
		double dt = frameEnd - frameStart;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		world.draw(window);
		window.display();
	}
}
int main(){
	play();
	return 0;
}