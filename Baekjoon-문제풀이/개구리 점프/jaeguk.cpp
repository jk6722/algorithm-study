#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

const int MAX_N = 100000 + 5;
int parent[MAX_N];

int N, Q;

int Find(int x) {
	if(parent[x] == x) return x;
	else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
	int parent_x = Find(x);
	int parent_y = Find(y);

	parent[parent_x] = parent_y;
}

void init() {
	for(int i = 0; i <= N; i++)
		parent[i] = i;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> Q;
	init();
	
	vector<pair<tiii, int>> logs;

	int x1, x2, y;
	for(int i = 1; i <= N; i++) {
		cin >> x1 >> x2 >> y;
		logs.push_back({{x1, x2, y}, i});
	}

	sort(logs.begin(), logs.end());

	for(int i = 0; i < logs.size() - 1; i++) {
		auto [now_x1, now_x2, now_y] = logs[i].first;
		int now_log_num = logs[i].second;

		for(int j = i + 1; j < logs.size(); j++) {
			auto [next_x1, next_x2, next_y] = logs[j].first;
			int next_log_num = logs[j].second;

			if(next_x1 > now_x2) break;

			if(Find(now_log_num) != Find(next_log_num)) {
				Union(now_log_num, next_log_num);
			}
		}
	}

	int q1, q2;
	for(int i = 0; i < Q; i++) {
		cin >> q1 >> q2;
		if(Find(q1) == Find(q2))
			cout << 1 << "\n";
		else cout << 0 << "\n";
	}

	return 0;
}