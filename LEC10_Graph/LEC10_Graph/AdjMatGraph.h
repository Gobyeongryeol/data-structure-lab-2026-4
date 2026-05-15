#pragma once
#define MAX_VTXS  20
#include <stdio.h>

class AdjMatGraph {
protected:
    int    size;
    char   vertices[MAX_VTXS];
    int    adj[MAX_VTXS][MAX_VTXS];
public:
    AdjMatGraph() { reset(); }
    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }

    // 그래프 초기화 ==> 공백 상태의 그래프
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }
    void insertVertex(char name) {
        if (!isFull()) vertices[size++] = name;
        else printf("Error: 그래프 정점 개수 초과\n");
    }
    // 간선 삽입: 무방향 그래프의 경우임. (방향, 가중치 그래프에서는 수정)
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1); // 방향 그래프에서는 삭제됨(<u,v>만 존재)
    }
    // 그래프 정보 출력 (화면이나 파일에 출력)
    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);		// 정점의 개수 출력
        for (int i = 0; i < size; i++) {		// 각 행의 정보 출력
            fprintf(fp, "%c ", getVertex(i));	// 정점의 이름 출력
            for (int j = 0; j < size; j++)	// 간선 정보 출력
                fprintf(fp, " %3d", getEdge(i, j));
            fprintf(fp, "\n");
    }
    }

};
class SrchAMGraph : public AdjMatGraph
{
    bool visited[MAX_VTXS];	 // 정점의 방문 정보
public:
    SrchAMGraph() { resetVisited(); }
    void resetVisited() {	// 모든 정점을 방문하지 않았다고 설정
        for (int i = 0; i < size; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

    // 깊이 우선 탐색 함수
    void DFS(int v) {
        visited[v] = true;	 // 현재 정점을 방문함
        printf("%c ", getVertex(v)); // 정점의 이름 출력

        for (int w = 0; w < size; w++)
            if (isLinked(v, w) && visited[w] == false)
            DFS(w);	 // 연결 + 방문X => 순환호출로 방문
    }
};
