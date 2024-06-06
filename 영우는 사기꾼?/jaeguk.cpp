#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;

const int MAX_N = 100000 + 5;
vector<unordered_map<int,int>> indegree(MAX_N);
vector<int> Edge[MAX_N];
unordered_set<int> Prev[MAX_N]; //선행 조건
int visited[MAX_N];
int N, M, K;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> K;

	int u, v;
	for(int i = 0; i < M; i++) {
		cin >> u >> v;
		indegree[v][u]++;
		Edge[u].push_back(v);
		Prev[v].insert(u);
	}

	// K개의 게임 정보
	int cmd, a;
	bool is_lier = false;
	for(int i = 0; i < K; i++) {
		cin >> cmd >> a;
		if(is_lier) continue;
		
		bool chk = false;
		switch(cmd) {
			case 1:
			// 건설			

			if(Prev[a].size() > 0) {
				//선행 건물이 남아 있다면
				is_lier = true;
			}
			else {
				// 문제가 없다면
				for(auto it : Edge[a]) {
					indegree[it][a]--;
					if(!indegree[it][a]) {
						Prev[it].erase(a);
					}
				}
				visited[a]++;
			}
			break;

			case 2:
			// 파괴
			if(!visited[a]) {
				//파괴할 건물이 없다면 거짓말
				is_lier = true;
			}
			else {
				visited[a]--;
				for(auto it : Edge[a]) {
					indegree[it][a]++;
					if(indegree[it][a] == 1)
						Prev[it].insert(a);
				}
			}
		}
	}

	string message = is_lier ? "Lier!" : "King-God-Emperor";
	cout << message << "\n";

	return 0;
}