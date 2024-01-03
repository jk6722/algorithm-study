#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 100 + 5;
pair<int,int> parent[MAX_N][MAX_N];
int N, M;
int Map[MAX_N][MAX_N];
vector<pair<int, int>> cheese;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

pair<int, int> Find(pair<int, int> x) {
    if (parent[x.first][x.second] == x) return x;
    return parent[x.first][x.second] = Find(parent[x.first][x.second]);
}

void Union(pair<int, int> x, pair<int, int> y) {
    pair<int, int> parent_x = Find(x);
    pair<int, int> parent_y = Find(y);
    parent[parent_x.first][parent_x.second] = parent_y;
}

bool isOk(pair<int, int> pos) {
    if (pos.first < 1 || pos.first > N || pos.second < 1 || pos.second > M) return false;
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            parent[i][j] = { i,j };
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> Map[i][j];
            if (Map[i][j] == 1) cheese.push_back({ i,j });
            else if (!Map[i][j]) {
                // 빈 칸이면
                for (int d = 0; d < 2; d++) {
                    pair<int, int> next = { i + dy[d], j + dx[d] };
                    if (isOk(next) && !Map[next.first][next.second]) {
                        // 인접한 빈 칸과 Union
                        pair<int, int> parent_next = Find(next);
                        pair<int, int> parent_now = Find({ i,j });
                        if(parent_next != parent_now)
                            Union(next, { i,j });
                    }
                }
            }
        }
    }

    int day = 0;
    while (!cheese.empty()) {
        vector<pair<int, int>> new_cheese; // 녹지 않은 치즈
        vector<pair<int, int>> melted; // 녹은 치즈
        day++;

        for (auto it : cheese) {
            int cnt = 0;
            for (int i = 0; i < 4; i++) {
                pair<int, int> next = { it.first + dy[i], it.second + dx[i] };
                if (isOk(next) && !Map[next.first][next.second] && (Find(next) == Find({ 1,1 }))) {
                    // 인접한 칸이 외부 공기라면
                    cnt++;
                }
            }
            if (cnt >= 2) {
                melted.push_back(it);
            }
            else new_cheese.push_back(it);
        }

        for (auto it : melted) {
            Map[it.first][it.second] = 0;
            for (int i = 0; i < 4; i++) {
                pair<int, int> next = { it.first + dy[i], it.second + dx[i] };
                if (isOk(next) && !Map[next.first][next.second]) {
                    Union(next, it);
                }
            }
        }

        cheese.clear();
        cheese = new_cheese;
    }

    cout << day << "\n";

    return 0;
}