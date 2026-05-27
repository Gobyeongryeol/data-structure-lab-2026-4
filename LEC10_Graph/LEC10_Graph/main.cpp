#include "AdjMatGraph.h"		// 그래프 클래스 포함
int main()
{
    SrchAMGraph g;		// DFS 탐색기능이 있는 그래프 객체 생성

    for (int i = 0; i < 7; i++)
        g.insertVertex('A' + i);	// 정점 삽입: 'A' 'B', ...
    g.insertEdge(0, 1);  // 간선 삽입
    g.insertEdge(1, 1);
    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);
    g.insertEdge(4, 5);
    g.insertEdge(3, 6);
    g.insertEdge(4, 6);
    printf("인접 행렬로 표현한 그래프\n");
    g.display();
    // 파일 출력
    FILE* fp;
    fopen_s(&fp, "../text_out.txt", "w"); 
    g.display(fp);
    fclose(fp);

    //DFS 탐색으로 방문
    printf("DFS ==> ");
    g.resetVisited();		// 모든 정점을 방문하지 않았다고 하고
    g.DFS(0);			// 0번째 정점(A)에서 깊이 우선 탐색 시작
    printf("\n");

    WGraph wg;
    wg.load("C:/Users/USER/Documents/data-structure-lab-2026-4/LEC10_Graph/graph.txt");
    wg.display();

    return 0;
}
