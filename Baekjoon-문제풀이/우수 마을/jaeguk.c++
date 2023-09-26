#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10000 + 5;
int popul[MAX_N];
vector<int> Edge[MAX_N];
int DP[MAX_N][2]; // [마을번호][우수마을 선정여부]
bool visited[MAX_N];

void dfs(int now) {
    visited[now] = true;

    DP[now][0] = 0;
    DP[now][1] = popul[now]; // 현재 마을이 우수마을이면 초기값은 현재 마을의 인구수

    for (auto it : Edge[now]) {
        int next = it;

        if (!visited[next]) {
            dfs(next);

            DP[now][0] += max(DP[next][0], DP[next][1]);
            DP[now][1] += DP[next][0];
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> popul[i];
    }

    int u, v;
    for(int i = 0; i<N-1;i++){
        cin >> u >> v;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }

    dfs(1);

    cout << max(DP[1][0], DP[1][1]) << "\n";

    return 0;
}