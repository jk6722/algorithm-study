#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 50 + 5;
const int INF = 987654321;
int N;
int dist[MAX_N][MAX_N];
int score[MAX_N];

void init() {
    for (int i = 1; i < MAX_N; i++) {
        for (int j = 1; j < MAX_N; j++) {
            dist[i][j] = INF;
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();

    cin >> N;
    int u, v;
    while (true) {
        cin >> u >> v;
        if (u == -1 && v == -1) break;
        dist[u][v] = 1;
        dist[v][u] = 1;
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int min_score = INF;
    for (int i = 1; i <= N; i++) {
        int score_ = 0;
        for (int j = 1; j <= N; j++) {
            if (i == j) continue;
            score_ = max(score_, dist[i][j]);
        }
        min_score = min(min_score, score_);
        score[i] = score_; // 가장 관계가 먼 사람과의 거리가 점수가 됨
    }

    vector<int> ans;
    for (int i = 1; i <= N; i++) {
        if (score[i] == min_score) ans.push_back(i);
    }

    cout << min_score << " " << ans.size() << "\n";
    for (auto it : ans) {
        cout << it << " ";
    }
    cout << "\n";

    return 0;
}