#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10000 + 5;
const int INF = INT_MAX;

int T;
int n, d, c;
vector<pair<int, int>>Edge[MAX_N];
vector<int> dist(MAX_N);

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;

    int a, b, s;
    while (T--) {
        fill(dist.begin(), dist.end(), INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        cin >> n >> d >> c;

        for (int i = 0; i < d; i++) {
            cin >> a >> b >> s;
            // b에서 a까지 감염시키는데 s초가 걸린다.
            Edge[b].push_back({ a,s });
        }
        pq.push({ 0, c });

        int ans = 0;
        int cnt = 0;

        while (!pq.empty()) {
            int cost = pq.top().first;
            int now = pq.top().second;
            pq.pop();

            if (dist[now] != INF) continue;

            dist[now] = cost;
            ans = cost;
            cnt++;

            for (int i = 0; i < Edge[now].size(); i++) {
                int next = Edge[now][i].first;
                int acost = Edge[now][i].second + cost;

                if (dist[next] == INF) pq.push({ acost, next });
            }
        }

        cout << cnt << " " << ans << "\n";

        for (int i = 1; i <= n; i++) {
            Edge[i].clear();
        }
    }

    return 0;
}