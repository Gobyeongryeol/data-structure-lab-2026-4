#pragma once
#include "AdjMatGraph.h"

class WGraphPrim : public WGraph {
public:
	int getMinVertex(bool* selected, int* dist) {
		int minv = 0;
		int mindist = INF;
		for(int v = 0; v < size; v++)
			if (!selected[v] && dist[v] < mindist) {
				mindist = dist[v];
				minv = v;
			}
		return minv;
	}

	void Prim(int s) {
		bool selected[MAX_VTXS];
		int dist[MAX_VTXS];

		for (int i = 0; i < size; i++) {
			dist[i] = INF;
			selected[i] = false;
		}
		dist[s] = 0;
		
		for (int i = 0; i < size; i++) {
			int u = getMinVertex(selected, dist);
			selected[u] = true;
			if (dist[u] == INF) return;
			printf("%c", getVertex(u));

			for (int v = 0; v < size; v++)
				if (getEdge(u, v) != INF)
					if (!selected[v] && getEdge(u, v) < dist[v])
						dist[v] = getEdge(u, v);
		}
	}
};