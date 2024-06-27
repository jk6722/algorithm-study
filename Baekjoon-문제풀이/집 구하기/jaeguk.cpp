#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;

const int MAX_N = 10000 + 5;
vector<pii> Edge[MAX_N];
unordered_set<int> macs; // 맥도날드 위치
unordered_set<int> stars; // 스타벅스 위치

unordered_map<int, int> mac_dist;
unordered_map<int, int> star_dist;

set<int> mac_adj; // 맥세권 집
set<int> star_adj; // 스세권 집

bool visited[MAX_N];

int V, E;
int M, x, S, y;

void get_mac_adj() {
	priority_queue<pii, vector<pii>, greater<pii>> q;
	for(auto it : macs)
		q.push({0, it});
	
	while(!q.empty()) {
		int now = q.top().second;
		int cost = q.top().first;
		q.pop();

		if(visited[now] || x < cost) continue;
		visited[now] = true;

		if(!macs.count(now) && !stars.count(now)) {
			// 집이면
			mac_adj.insert(now);
			mac_dist[now] = cost;
		}

		for(int i = 0; i < Edge[now].size(); i++) {
			int next = Edge[now][i].first;
			int acost = cost + Edge[now][i].second;

			if(!visited[next] && acost <= x && !macs.count(next)) {
				q.push({acost, next});
			}
		}
	}
}

void get_star_adj() {
	priority_queue<pii, vector<pii>, greater<pii>> q;
	for(auto it : stars)
		q.push({0, it});
	
	while(!q.empty()) {
		int now = q.top().second;
		int cost = q.top().first;
		q.pop();

		if(visited[now] || y < cost) continue;
		visited[now] = true;

		if(!macs.count(now) && !stars.count(now)) {
			// 집이면
			star_adj.insert(now);
			star_dist[now] = cost;
		}

		for(int i = 0; i < Edge[now].size(); i++) {
			int next = Edge[now][i].first;
			int acost = cost + Edge[now][i].second;

			if(!visited[next] && acost <= y && !stars.count(next)) {
				q.push({acost, next});
			}
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> V >> E;

	int u, v, w;
	for(int i = 0; i < E; i++) {
		cin >> u >> v >> w;
		Edge[u].push_back({v, w});
		Edge[v].push_back({u, w});
	}

	cin >> M >> x;
	for(int i = 0; i < M; i++) {
		cin >> u;
		macs.insert(u);
	}

	cin >> S >> y;
	for(int i = 0; i < S; i++) {
		cin >> u;
		stars.insert(u);
	}

	get_mac_adj();
	memset(visited, false, sizeof(visited));
	get_star_adj();

	int ans = INT_MAX;
	for(auto pos : mac_adj) {
		if(star_adj.count(pos)) {
			// 맥세권, 스세권 모두에 포함되면
			ans = min(ans, mac_dist[pos] + star_dist[pos]);
		}
	}

	ans = ans == INT_MAX ? -1 : ans;
	cout << ans << "\n";

	return 0;
}