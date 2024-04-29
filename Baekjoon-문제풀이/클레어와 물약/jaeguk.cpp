#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, M;
const int MAX_N = 200000 + 5;
vector<int> adj[MAX_N]; //i번째 물약을 사용해서 만들 수 있는 물약
int indegree[MAX_N]; //각 물약을 만들기 위해서 필요한 선행 물약의 수
set<int> can_make; //만들 수 있는 물약
bool visited[MAX_N];
map<int, int> itor; //물약 번호 매핑

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	int k, x, r;
	for(int i = 0; i < M; i++) {
		vector<int> temp;

		cin >> k;
		for(int j = 0; j < k; j++) {
			cin >> x;
			adj[x].push_back(i);
		}

		cin >> r;
		itor[i] = r;
		indegree[i] = k;
	}

	int L, y;
	cin >> L;

	queue<int> q; //현재 가지고 있는 물약
	for(int i = 0; i < L; i++) {
		cin >> y;
		q.push(y);
		can_make.insert(y);
	}

	while(!q.empty()) {
		int now = q.front();
		q.pop();

		if(visited[now]) continue;
		visited[now] = true;

		for(auto it : adj[now]) {
			indegree[it]--;

			if(!indegree[it]) {
				// 모든 재료가 준비되었다면
				q.push(itor[it]);
				can_make.insert(itor[it]);
			}
		}
	}

	cout << can_make.size() << "\n";
	for(auto it : can_make)
		cout << it << " ";
	cout << "\n";

	return 0;
}