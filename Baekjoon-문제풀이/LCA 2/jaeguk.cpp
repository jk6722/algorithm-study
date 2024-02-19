#include<vector>
#include<cstring>
#include<iostream>
#include<queue>

using namespace std;

//LGN = 5; // 2^4 (16) < N = 18 < 2^5 (32)
// 2^16 (65,536) < N = 100,000 < 2^17 (131,072)

const int LGN = 17; 
const int MAX_N = 100000 + 5;

int parent[LGN + 1][MAX_N];
int depth[MAX_N]; //루트로부터의 깊이
bool visited[MAX_N];
vector<int>adj[MAX_N];
int N, M;

void bfs(int st, int dep) {
	queue<int> q;
	q.push(st);

	depth[st] = dep;
	visited[st] = true;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (auto adj_node : adj[now]) {
			if (!visited[adj_node]) {
				visited[adj_node] = true;
				// parent[i][j]에는 j 의 2^i 번째 부모 저장
				// parent[0][j]에는 j의 직속 부모가 저장된다
				parent[0][adj_node] = now;
				depth[adj_node] = depth[now] + 1;
				q.push(adj_node);
			}
		}
	}
}

// 2^K 번째 조상들을 다 저장
void aces_find() {
	//조상을 빠르게 찾기 위함
	// K = 0인 경우(직속 부모)에 대해서는 BFS에서 다 저장해두었다
	for (int K = 1; K <= LGN; K++) {
		for (int V = 1; V <= N; V++) {
			parent[K][V] = parent[K - 1][parent[K - 1][V]];
		}
	}
}

void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}

// x 와 y 의 공통 조상 찾기
int lca(int x, int y) {
	// 루트 기준에서 더 아래에 있는 정점을 y, 더 높이있는 정점을 x로 설정한다
	if (depth[x] > depth[y]) {
		//x가 더 아래에 있다면
		swap(x, y);
	}

	//y의 depth가 x의 depth와 같아질 때까지 y를 끌어올려서 높이가 같아지게 한다
	for (int i = LGN; i >= 0; i--) {
		// (1 << i) = 2^i
		if (depth[y] - depth[x] >= (1 << i)) {
			//2^i 높이만큼 뛰어도 되면
			y = parent[i][y]; //y의 2^i번째 부모를 y로 설정 => y가 2^i만큼 위로 뛴다
		}
	}

	//현재 x와 y의 높이는 같다

	//높이가 같은데, 노드도 같다면 공통조상
	if (x == y)
		return x;

	//노드가 다르다면, 공통조상을 찾아서 올라감
	for (int i = LGN; i >= 0; i--) {
		if (parent[i][x] != parent[i][y]) {
			//다르다는 것은 위쪽 범위에 공통 조상이 존재한다는 것이므로 올라감
			x = parent[i][x];
			y = parent[i][y];
		}
		//같은 경우에 break를 하지 않는 이유는
		//공통 조상을 찾았다고해도 그 조상이 "최소" 공통 조상이라는 보장이 없기 때문에 더 내려가봄
	}

	return parent[0][x];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	int u, v;
	for (int i = 1; i < N; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}


	// DFS로 돌리면 Stack Overflow 발생 => BFS 사용
	bfs(1, 0);
	aces_find();

	cin >> M;
	for (int i = 1; i <= M; i++) {
		int a, b;
		cin >> a >> b;
		cout << lca(a, b) << "\n";
	}
	cout << "\n";

	return 0;
}