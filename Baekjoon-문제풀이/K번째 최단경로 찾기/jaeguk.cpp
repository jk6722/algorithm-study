#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<tuple>
using namespace std;

const int MAX_N = 1000 + 5;
const int INF = 987654321;
vector<pair<int, int>> Edge[MAX_N];
priority_queue<int> Dist[MAX_N]; //최대 K개의 코스트만 저장한다
int n, m, k;

void dijkstra(int st) {
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, st });

	Dist[st].push(0);

	while (!pq.empty()) {
		int cost = pq.top().first;
		int now = pq.top().second;
		pq.pop();

		for (auto it : Edge[now]) {
			int next = it.first;
			int acost = it.second + cost;

			if (Dist[next].size() < k) {
				Dist[next].push(acost);
				pq.push({ acost, next });
			}
			else if (Dist[next].size() == k && Dist[next].top() > acost) {
				Dist[next].pop();
				Dist[next].push(acost);
				pq.push({ acost, next });
			}
		}

	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		Edge[u].push_back({ v,w });
	}

	dijkstra(1);

	for (int i = 1; i <= n; i++) {
		if (Dist[i].size() < k) cout << "-1\n";
		else cout << Dist[i].top() << "\n";
	}
	return 0;
}