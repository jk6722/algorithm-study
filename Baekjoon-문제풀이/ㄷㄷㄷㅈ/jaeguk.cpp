#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

const int MAX_N = 300000 + 5;
int indegree[MAX_N];
vector<int> Edge[MAX_N];
map<pii, bool> visited;
int N;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	int u, v;
	for(int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		Edge[u].push_back(v);
		Edge[v].push_back(u);
		indegree[u]++;
		indegree[v]++;
	}

	int D = 0;
	int G = 0;
	for(int i = 1; i <= N; i++) {
		if(indegree[i] >= 3) {
			int n = indegree[i];
			G += n * (n - 1) * (n - 2) / 6;
		}
	}
	
	for(int i = 1; i <= N; i++) {
		for(auto adj : Edge[i]) {
			if(visited[{adj, i}] == true || visited[{i, adj}] == true) continue;

			if(indegree[adj] >= 2 && indegree[i] >= 2) {
				D += (indegree[adj] - 1) * (indegree[i] - 1);
				visited[{adj, i}] = true;
			}
		}
	}

	string ans = D == G * 3 ? "DUDUDUNGA" : D > G * 3 ? "D" : "G";
	cout << ans << "\n";

	return 0;
}