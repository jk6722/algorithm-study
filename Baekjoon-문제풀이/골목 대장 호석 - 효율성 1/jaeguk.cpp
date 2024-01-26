#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
const int INF = 987654321;
vector<pair<int,int>> Edge[MAX_N];
vector<int> dist(MAX_N, INF);
int N, M, A, B, C;

void dijkstra(int maxShame) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, A});

    while(!pq.empty()) {
        int cost = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        if(dist[now] != INF || cost > C) continue;
        dist[now] = cost;

        if(now == B) break;

        for(auto it : Edge[now]) {
            int acost = cost + it.second;
            int next = it.first;
            if(dist[next] != INF || acost > C || it.second > maxShame) continue;
            pq.push({acost, next});
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> A >> B >> C;

    int u, v, w;
    int L = INF, R = 0;

    for(int i = 1; i<=M; i++) {
        cin >> u >> v >> w;
        Edge[u].push_back({v, w});
        Edge[v].push_back({u, w});
        L = min(L, w);
        R = max(R, w);
    }

    int ans = INF;

    while(L <= R) {
        fill(dist.begin(), dist.end(), INF);
        int mid = (L + R) / 2;
        dijkstra(mid);
        if(dist[B] <= C) {
            ans = min(ans, mid);
            R--;
        }
        else {
            L++;
        }
    }
    ans = ans == INF ? -1 : ans;
    cout << ans << "\n";
    return 0;
}