#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

const int MAX_N = 100000 + 5;
vector<int> Edge[MAX_N];
bool visited[MAX_N];
int N, M;

int node_cnt = 0;
int edge_cnt = 0;

void dfs(int now) {
	node_cnt++;
	visited[now] = true;

	for(auto next : Edge[now]) {
		edge_cnt++;
		if(!visited[next]) dfs(next);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >> N >> M;

	int u, v;
	for(int i = 0; i < M; i++) {
		cin >> u >> v;
		Edge[u].push_back(v);
		Edge[v].push_back(u);
	}

	int group_cnt = 0; //분리된 집합이 몇개인지

	int ans = 0;

	for(int i = 1; i <= N; i++) {
		if(!visited[i]) {
			node_cnt = 0;
			edge_cnt = 0;
			dfs(i);
			ans += (edge_cnt / 2 - (node_cnt - 1)); //끊어야 할 엣지 수
			group_cnt++;
		}
	}

	ans += (group_cnt - 1); //모든 분리 집합 사이를 연결
	cout << ans << "\n";
	
	return 0;
}