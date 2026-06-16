A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}


def bfs(A):
    """0번 노드부터 BFS 순서로 그래프를 탐색한 결과를 반환한다.

    BFS는 큐(queue)를 사용하여 현재 노드와 가까운 노드부터 방문한다.
    같은 깊이의 노드가 여러 개 있을 때는 번호가 작은 노드를 먼저 방문하기 위해
    인접 노드 리스트를 오름차순으로 정렬하여 큐에 넣는다.

    Args:
        A (dict): 각 노드와 인접 노드 목록을 저장한 인접 리스트 그래프

    Returns:
        list: BFS로 방문한 노드 번호의 순서
    """
    answer = []
    visited = set([0])
    queue = [0]

    while queue:
        node = queue.pop(0)
        answer.append(node)

        for next_node in sorted(A[node]):
            if next_node not in visited:
                visited.add(next_node)
                queue.append(next_node)

    return answer



def dfs(A):
    """0번 노드부터 DFS 순서로 그래프를 탐색한 결과를 반환한다.

    DFS는 스택(stack)을 사용하여 한 방향으로 깊게 들어가며 방문한다.
    번호가 작은 노드를 먼저 방문해야 하므로, 스택에는 인접 노드를 큰 번호부터
    넣는다. 이렇게 하면 나중에 들어간 작은 번호의 노드가 먼저 pop되어 방문된다.
    또한 중복 삽입을 막기 위해 스택에 넣는 순간 방문 처리한다.

    Args:
        A (dict): 각 노드와 인접 노드 목록을 저장한 인접 리스트 그래프

    Returns:
        list: DFS로 방문한 노드 번호의 순서
    """
    answer = []
    visited = set([0])
    stack = [0]

    while stack:
        node = stack.pop()
        answer.append(node)

        for next_node in sorted(A[node], reverse=True):
            if next_node not in visited:
                visited.add(next_node)
                stack.append(next_node)

    return answer


# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0, 1, 2, 3, 4, 5, 6]
assert dfs_result == [0, 1, 4, 5, 2, 6, 3]
print('PASSED!')
