#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 10 + 1;
const int INF = 987654321;
int N, K;
int dist[MAX_N][MAX_N];
int ans = INF;
bool visited[MAX_N];

void floyd() {
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

void backtracking(int now, int cost, int depth) {
    if (depth == N) {
        ans = min(ans, cost);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (now == i || visited[i]) continue;
        int next = i;
        int acost = cost + dist[now][next];
        visited[next] = true;
        backtracking(next, acost, depth + 1);
        visited[next] = false;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> dist[i][j];
       }
    }

    floyd();
    visited[K] = true;
    backtracking(K, 0, 1);
    cout << ans << "\n";
    return 0;
}