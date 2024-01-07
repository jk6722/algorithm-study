#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 200000000 + 5;
int N, K;
int dx[] = { -1, 1 };
set<int> visited;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    int pos;
    queue<int> q;
    for (int i = 0; i < N; i++) {
        cin >> pos;
        q.push(pos);
        visited.insert(pos);
    }

    int remain = K;
    ll ans = 0;
    ll dist = 1;

    while (!q.empty()) {
        int iter = q.size();

        for (int j = 0; j < iter; j++) {
            int now = q.front();
            q.pop();

            for (int i = 0; i < 2; i++) {
                int next = now + dx[i];
                if (!visited.count(next)) {
                    // 방문되지 않은 곳이면 (집을 지어야 함)
                    q.push(next);
                    visited.insert(next);
                    ans += dist;
                    if (--remain == 0) goto Lend;
                }
            }
        }

        dist++;
    }

    Lend:
    cout << ans << "\n";

    return 0;
}