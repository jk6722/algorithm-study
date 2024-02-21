#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<tuple>
using namespace std;
using ll = long long;

const int MAX_N = 75000 + 5;

vector<pair<int, int>> islands;
int tree[MAX_N];
int T, N, start;

bool cmp_y(pair<int, int> pos1, pair<int, int> pos2) {
	if (pos1.second < pos2.second) return true;
	else if (pos1.second == pos2.second) return pos1.first > pos2.first;
	else return false;
}

bool cmp_x(pair<int, int> pos1, pair<int, int> pos2) {
	if (pos1.first > pos2.first) return true;
	else if (pos1.first == pos2.first) return pos1.second < pos2.second;
	else return false;
}

void update(int idx) {
	while (idx <= N) {
		tree[idx]++;
		idx += idx & -idx;
	}
}

int query(int idx) {
	int sum = 0;

	while (idx > 0) {
		sum += tree[idx];
		idx -= idx & -idx;
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	while (T--) {
		cin >> N;

		islands.clear();
		memset(tree, 0, sizeof(tree));

		int x, y;
		for (int i = 1; i <= N; i++) {
			cin >> x >> y;
			islands.push_back({ x, y });
		}

		//섬의 좌표를 y좌표 기준으로 오름차순 정렬
		sort(islands.begin(), islands.end(), cmp_y);

		int y_value = 1;
		int prev = islands[0].second;

		islands[0].second = y_value;
		for (int i = 1; i < islands.size(); i++) {
			//y좌표 다시 라벨링 (좌표 압축) => 1 ~ 최대 N
			if (islands[i].second > prev) y_value++;
			prev = islands[i].second;
			islands[i].second = y_value;
		}

		//섬의 좌표를 x좌표 기준으로 다시 내림차순 정렬
		sort(islands.begin(), islands.end(), cmp_x);

		ll cnt = 0;
		for (auto island : islands) {
			//현재 섬보다 y좌표가 작은 섬이 몇 개 있는지 알아내야 함
			cnt += (ll)query(island.second);
			update(island.second);
		}

		cout << cnt << "\n";
	}


	return 0;
}