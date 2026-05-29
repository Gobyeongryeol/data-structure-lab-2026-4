#include "AdjMatGraph.h"

int main()
{
    SrchAMGraph g;

    for (int i = 0; i < 7; i++)
        g.insertVertex('A' + i);

    g.insertEdge(0, 1);
    g.insertEdge(1, 1);
    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);
    g.insertEdge(4, 5);
    g.insertEdge(3, 6);
    g.insertEdge(4, 6);

    printf("인접 행렬로 표현한 그래프\n");
    g.display();

    FILE* fp;
    fopen_s(&fp, "../text_out.txt", "w");

    if (fp != NULL) {
        g.display(fp);
        fclose(fp);
    }

    printf("DFS ==> ");
    g.resetVisited();
    g.DFS(0);
    printf("\n\n");

    WGraph wg;

    wg.load("C:/Users/USER/Documents/data-structure-lab-2026-4/LEC10_Graph/graph.txt");

    printf("입력 그래프: graph.txt\n");
    wg.display();
    printf("\n");

    WGraphMST mst;

    mst.load("C:/Users/USER/Documents/data-structure-lab-2026-4/LEC10_Graph/graph.txt");

    printf("MST By Kruskal's Algorithm\n");

    mst.Kruskal();

    return 0;
}