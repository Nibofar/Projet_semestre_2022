#pragma once

#include <unordered_map>
#include <algorithm>

#include "SFML/System/Vector2.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

namespace std {
	template <> struct hash<sf::Vector2i> {
		inline std::size_t operator()(const sf::Vector2i& k) const {
			using std::hash;
			return std::size_t((k.y << 12) + k.x);
		};
	};
}

typedef std::unordered_map<sf::Vector2i, bool>			BaseGraph;
typedef std::unordered_map<sf::Vector2i, float>			DistanceGraph;
typedef std::unordered_map<sf::Vector2i, sf::Vector2i>	AssocGraph;
typedef std::vector<sf::Vector2i>						VertexList;

class Dijkstra{
public:
	sf::Vector2i	start = sf::Vector2i(-1,-1);
	BaseGraph		g;//les sommets
	DistanceGraph	d;//les distances
	AssocGraph		pred;//a tout sommet S1 -> S2, qui est le predecesseur dans le chemin S1 -> Start => s2 

	Dijkstra() {
	};

	void setGraph(BaseGraph& _g){
		g = _g;
		d.clear();
		pred.clear();
	}

	void init(sf::Vector2i _start) {
		start = _start;
		d.reserve(g.size());
		for (auto& s : g)
			d[s.first] = 1024 * 1024;
		d[start] = 0;
	};

	//Q ?
	int findMin(VertexList& q) {
		float mini = 1024 * 1024;
		int vertexIdx = -1;
		int idx = 0;
		for (sf::Vector2i & s : q) {
			if (d[s] < mini) {
				mini = d[s];
				vertexIdx = idx;
			}
			idx++;
		}
		return vertexIdx;
	};

	inline float heur(sf::Vector2i s1, sf::Vector2i s2) {
		float dx = s2.x - s1.x;
		float dy = s2.y - s1.y;
		return sqrt(dx * dx + dy * dy);
	};

	std::vector<sf::Vector2i> getPath(sf::Vector2i dest);

	inline void updateDist(sf::Vector2i s1, sf::Vector2i s2) {
		float ndist = d[s1] + heur(s1, s2);
		if (d[s2] > ndist) {
			d[s2] = ndist;
			pred[s2] = s1;
		}
	};

	void build(sf::Vector2i _start);

	void im(){
		using namespace ImGui;
		Value("start x", start.x);
		Value("start y", start.y);
		if( TreeNode("Preds")){
			int idx = 0;
			for(auto & p: pred){
				if( TreeNode(std::to_string(idx).c_str())){
					ImGui::LabelText("v","%d,%d -> %d,%d", p.first.x,p.first.y, p.second.x,p.second.y );
					TreePop();
				}
				idx++;
			}
			TreePop();
		}
	}

	//
};