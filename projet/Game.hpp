#pragma once
#include <SFML/Graphics.hpp>
struct Game {
public:
	static const int WIDTH = 800;
	static const int HEIGHT = 608;
	static inline constexpr int CELL_SIZE = 16;
	static const int CELL_X = WIDTH / CELL_SIZE;
	static const int CELL_Y = HEIGHT / CELL_SIZE;
};