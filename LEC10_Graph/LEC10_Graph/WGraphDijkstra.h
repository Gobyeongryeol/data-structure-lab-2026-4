#pragma once
#include "AdjMatGraph.h"
#include "WGraphPrim.h"

class WGraphDijkstra : public WGraph {
	int dist[MAX_VTXS];
	bool found[MAX_VTXS];
public:
	int chooseVertex() {
		int min = INF;
		int minpos = -1;
		for(int i = 0; i < size ;i++)
			if (dist[i] < min && !found[i]) {
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() {
		for (int i = 0; i < size; i++)
			printf("%5d", dist[i]);
		printf("\n");
	}
	void ShortestPath(int start) {
		for (int i = 0; i < size; i++) {
			dist[i] = getEdge(start, i);
			found[i] = false;
		}
		found[start] = true;
		dist[start] = 0;
		for (int i = 0; i < size; i++) {
			printf("Step%2d:", i + 1);
			printDistance();
			int u = chooseVertex();
			found[u] = true;
			for (int w = 0; w < size; w++) {
				if (found[w] == false)
					if (dist[u] + getEdge(u, w) < dist[w])
						dist[w] = dist[u] + getEdge(u, w);
			}
		}
	}
};