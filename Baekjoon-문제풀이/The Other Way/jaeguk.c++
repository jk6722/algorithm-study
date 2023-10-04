#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 9;
const int MAX_N = 100000 + 5;
const ll INF = LLONG_MAX;
int N, M, S, E;

vector<pair<int, ll>> Edge[MAX_N];
vector<pair<ll, int>> Dist(MAX_N, { INF, 0 });

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> S >> E;

    int u, v, w;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        Edge[u].push_back({ v,w });
        Edge[v].push_back({ u,w });
    }

    priority_queue<tuple<ll, int>, vector<tuple<ll, int>>, greater<tuple<ll, int>>> pq;

    pq.push({ 0, S });
    Dist[S].second = 1;
    
    while (!pq.empty()) {
        auto [cost, now] = pq.top();
        pq.pop();

        // 의미없는 방문
        if (Dist[now].first < cost) continue;
        Dist[now].first = cost;

        for (auto edge : Edge[now]) {
            int next = edge.first;
            ll acost = cost + edge.second;

            // 최단 거리가 아니면 패스
            if (Dist[next].first < acost) continue;

            // 이미 방문된 곳인데, 거리가 같다면
            else if (Dist[next].first == acost) {
                // count만 증가
                Dist[next].second = (Dist[next].second + Dist[now].second) % MOD;
                continue;
            }
            // 현재가 최단거리라면
            Dist[next].first = acost;
            Dist[next].second = Dist[now].second;
            // 최단 거리가 갱신될 때만 큐에 넣음
            pq.push({ acost, next });
        }
    }

    cout << Dist[E].second << "\n";

    return 0;
}