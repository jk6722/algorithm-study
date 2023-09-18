#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
const int MAX_N = 100000 + 5;
vector<int> Edge[MAX_N];

int order[MAX_N];
bool visited[MAX_N];

int ans = 1;
vector<int> correct_order;
vector<int> visit_order; // 방문 순서

bool comp(int a, int b) {
	return order[a] < order[b];
}

void dfs(int now) {
	visited[now] = true;
	visit_order.push_back(now);
	for (int i = 0; i < Edge[now].size(); i++) {
		int next = Edge[now][i];
		if (!visited[next])
			dfs(next);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	int u, v;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		Edge[u].push_back(v);
		Edge[v].push_back(u);
	}

	int st = 0;
	int node;
	for (int i = 1; i <= N; i++) {
		cin >> node;
		correct_order.push_back(node);
		order[node] = i;
	}

	// 모든 간선을 방문 순서를 기준으로 정렬
	for (int i = 1; i <= N; i++)
		sort(Edge[i].begin(), Edge[i].end(), comp);

	dfs(1);

	// 방문해야 하는 순서와 다르면 답은 0
	for (int i = 0; i < N; i++) {
		if (visit_order[i] != correct_order[i]) {
			ans = 0;
			break;
		}
	}

	cout << ans << "\n";
	return 0;
}