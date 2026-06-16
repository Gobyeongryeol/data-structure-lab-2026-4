import sys
from collections import deque

## 입력 받는 코드입니다. 수정할 필요 없습니다.
try:
    sys.stdin = open('case.txt')
except FileNotFoundError:
    pass
N, M = list(map(int, input().split()))
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
# print(concerts)
# [[1, 0, 0, 1, 1, 0], [1, 0, 1, 1, 0, 0], [1, 1, 1, 1, 0, 1], [0, 1, 1, 0, 1, 1], [0, 1, 0, 0, 1, 0]]
###################################


def count_stages(concerts):
    """콘서트장 약도에서 독립적인 무대 공간의 개수를 계산한다.

    약도에서 0은 무대 공간, 1은 펜스를 의미한다. 상하좌우로 연결된 0들은
    하나의 독립적인 무대 공간으로 본다. 전체 격자를 순회하다가 아직 방문하지
    않은 0을 발견하면 새로운 무대 공간을 찾은 것이므로 개수를 1 증가시키고,
    BFS로 연결된 모든 0을 방문 처리한다.

    Args:
        concerts (list): 0과 1로 이루어진 N x M 크기의 2차원 리스트

    Returns:
        int: 서로 분리된 무대 공간의 개수
    """
    if not concerts:
        return 0

    answer = 0
    n = len(concerts)
    m = len(concerts[0])
    visited = [[False] * m for _ in range(n)]
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    for r in range(n):
        for c in range(m):
            if concerts[r][c] == 0 and not visited[r][c]:
                answer += 1
                queue = deque([(r, c)])
                visited[r][c] = True

                while queue:
                    cur_r, cur_c = queue.popleft()

                    for dr, dc in directions:
                        nr = cur_r + dr
                        nc = cur_c + dc

                        if nr < 0 or nr >= n or nc < 0 or nc >= m:
                            continue
                        if visited[nr][nc]:
                            continue
                        if concerts[nr][nc] == 1:
                            continue

                        visited[nr][nc] = True
                        queue.append((nr, nc))

    return answer


print(count_stages(concerts))
