#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 10 + 5;
int H[MAX_N][MAX_N];
int W[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int T, R, C;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

bool isOk(pair<int, int> pos) {
    if (pos.first < 1 || pos.first > R || pos.second < 1 || pos.second > C) return false;
    return true;
}

bool bfs(pair<int, int> st) {
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int>> q;
    q.push(st);

    int water = 1001; // MAX
    bool fillWater = true; // 물을 채울 수 있는지에 대한 여부
    vector<pair<int, int>> same; // 현재 칸과 같은 높이의 섬들

    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        if (visited[now.first][now.second]) continue;
        visited[now.first][now.second] = true;
        same.push_back(now);

        for (int i = 0; i < 4; i++) {
            pair<int, int> next = { now.first + dy[i], now.second + dx[i] };
            if (!isOk(next)) {
                // 낭떠러지와 연결되어 있다면 물을 채울 수 없음
                fillWater = false;
                goto lend;
            }
            if (!visited[next.first][next.second] && (W[next.first][next.second] == W[now.first][now.second])) {
                // 같은 높이이면
                q.push(next);
                continue;
            }
            if (W[next.first][next.second] < W[now.first][now.second]) {
                // 인접한 곳의 높이가 더 낮으면
                fillWater = false;
                goto lend;
            }
            else if (W[next.first][next.second] > W[now.first][now.second]) {
                // 인접한 곳의 높이가 더 높으면
                water = min(water, W[next.first][next.second]);
            }
        }
    }
    
    lend:
    if (fillWater) {
        for (auto it : same) {
            W[it.first][it.second] = water;
        }
        return true;
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    for(int t = 1; t <=T; t++) {
        memset(H, 0, sizeof(H));

        cin >> R >> C;
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                cin >> H[i][j];
                W[i][j] = H[i][j];
            }
        }

        loop:
        for (int i = 2; i < R; i++) {
            for (int j = 2; j < C; j++) {
                if (bfs({ i,j })) {
                    // 물 높이에 변화가 발생하면 처음부터 다시 탐색
                    goto loop;
                }
            }
        }

        int ans = 0;
        for (int i = 2; i < R; i++) {
            for (int j = 2; j < C; j++) {
                ans += (W[i][j] - H[i][j]);
            }
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}