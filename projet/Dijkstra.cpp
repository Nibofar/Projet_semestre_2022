#include "Dijkstra.hpp"

std::vector<sf::Vector2i> Dijkstra::getPath(sf::Vector2i dest) {
	std::vector<sf::Vector2i> res;
	sf::Vector2i cur = dest;
	while (cur != start) {
		res.push_back(cur);
		sf::Vector2i next = pred[cur];
		if (next == cur)
			break;
		cur = next;
	}

	return res;
}

void Dijkstra::build(sf::Vector2i _start) {
	init(_start);
	VertexList q;
	q.resize(g.size());
	for (auto& p : g)
		q.push_back(p.first);

	sf::Vector2i tldr[4] = {
		sf::Vector2i(0,1),
		sf::Vector2i(0,-1),
		sf::Vector2i(1,0),
		sf::Vector2i(-1,0),
	};

	sf::Vector2i s2;
	sf::Vector2i s1;
	while (!q.empty()) {
		int s1Idx = findMin(q);
		if (s1Idx == -1) break;

		s1 = q[s1Idx];
		q.erase(q.begin() + s1Idx);

		for (int i = 0; i < 4; ++i) {
			auto s2 = tldr[i] + s1;
			if (g.find(s2) == g.end()) continue;
			updateDist(s1, s2);
		}
	}
}