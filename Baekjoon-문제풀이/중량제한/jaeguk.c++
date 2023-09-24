#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 10000 + 5;
int N, M, st, ed;
vector<pair<int, ll>> Edge[MAX_N];
bool visited[MAX_N];

bool is_ok(ll Mid) {
    queue<int> q;
    memset(visited, false, sizeof(visited));

    q.push(st);
    visited[st] = true;

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        if (now == ed) return true;

        for (auto it : Edge[now]) {
            int next = it.first;
            ll aweight = it.second;
            if (!visited[next] && aweight >= Mid) {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    int A, B;
    ll C;

    ll L = 0, R = 0;
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        Edge[A].push_back({ B,C });
        Edge[B].push_back({ A,C });
        R = max(R, C);
    }

    cin >> st >> ed;

    ll ans = L;
    while (L <= R) {
        ll Mid = (L + R) / 2;

        if (is_ok(Mid)) {
            L = Mid + 1;
            ans = max(ans, Mid);
        }
        else R = Mid - 1;
    }

    cout << ans << "\n";
    return 0;
}