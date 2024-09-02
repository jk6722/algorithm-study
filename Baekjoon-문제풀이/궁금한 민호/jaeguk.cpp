#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

const int MAX_N = 20 + 5;
const int INF = 987654321;
int min_dist[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
vector<tiii> need; // 필요한 도로
priority_queue<tiii, vector<tiii>, greater<>> pq;
int N;

void init() {
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			dist[i][j] = i == j ? 0 : INF;
		}
	}
}

void floyd() {
	for(auto [u, v, w] : need) {
		dist[u][v] = w;
		dist[v][u] = w;
	}

	for(int k = 1; k <= N; k++) {
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

bool is_ok() {
	init();
	floyd();
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			if(dist[i][j] != min_dist[i][j]) return false;
		}
	}
	return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >> N;
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			cin >> min_dist[i][j];
			if(i < j) pq.push({min_dist[i][j], i, j});
		}
	}

	while(!pq.empty()) {
		auto [weight, from, to] = pq.top();
		pq.pop();

		init();
		floyd();

		if(dist[from][to] == min_dist[from][to]) continue;
		need.push_back({from, to, weight});
	}


	if(is_ok()) {
		int ans = 0;
		for(auto [u, v, w] : need) ans += w;
		cout << ans << "\n";
	}
	else cout << "-1\n";

	return 0;
}