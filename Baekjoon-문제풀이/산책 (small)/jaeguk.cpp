#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAX_N = 10000 + 5;
const int INF = 987654321;

// Edge를 정렬한 후 순차적으로 방문하면 사전순으로 방문하게 될 것
set<int> Edge[MAX_N];
vector<int> dist(MAX_N, INF);
set<int> prevNode[MAX_N]; //이전에 방문한 노드
set<vector<int>> routes;

int N, M, S, E;

void backtracking(int now, vector<int> route) {
    if (*prevNode[now].begin() == -1) {
        vector<int> reversed;
        for (int i = route.size() - 1; i >= 0; i--) reversed.push_back(route[i]);
        routes.insert(reversed);
        return;
    }

    for (auto prev : prevNode[now]) {
        route.push_back(prev);
        backtracking(prev, route);
        route.pop_back();
    }
}

void setting(int st, int ed) {
    vector<int> route;
    backtracking(ed, route);

    vector<int> visited = *routes.begin();

    for (auto node : visited)
        dist[node] = 0;
    dist[st] = INF;
    dist[ed] = INF;
}

void dijkstra(int st, int ed) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push({ 0, st, -1 });

    while (!pq.empty()) {
        auto top = pq.top();

        int cost = get<0>(top);
        int now = get<1>(top);
        int prev = get<2>(top);

        pq.pop();
        
        if (dist[now] < cost) continue;
        else if (dist[now] == cost) {
            prevNode[now].insert(prev);
        }
        else if (dist[now] > cost) {
            dist[now] = cost;
            prevNode[now].clear();
            prevNode[now].insert(prev);
        }

        if (now == ed) break;

        for (int next : Edge[now]) {
            int acost = cost + 1;
            if (dist[next] >= acost && prevNode[next].count(now) == 0)
                pq.push({ acost, next, now });
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> M;

    int u, v;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        Edge[u].insert(v);
        Edge[v].insert(u);
    }

    cin >> S >> E;

    int ans = 0;

    dijkstra(S, E);
    ans += dist[E];

    fill(dist.begin(), dist.end(), INF);
    setting(S, E);

    dijkstra(E, S);
    ans += dist[S];

    cout << ans << "\n";

    return 0;
}