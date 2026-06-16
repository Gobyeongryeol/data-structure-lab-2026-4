#include "WGraphPrim.h"
#include "WGraphDijkstra.h"

int main() {
    const char* filename = R"(0605.txt)";

    WGraphPrim g;
    g.load(filename);
    printf("MST By Prim's Algorithm\n");
    g.Prim(0);

    printf("\n");

    WGraphDijkstra h;
    h.load(filename);
    printf("Shortest Path By Dijkstra Algorithm\n");
    h.ShortestPath(0);

    return 0;
}