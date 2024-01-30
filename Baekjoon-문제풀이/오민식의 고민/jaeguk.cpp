#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 50 + 5;
const ll INF = LLONG_MAX;

int Earn[MAX_N];
vector<ll> Dist(MAX_N, INF);
vector<tuple<int,int,ll>> Edges;
vector<int> Edge[MAX_N];
queue<int> Cycles;

bool visited[MAX_N];
int N, M, st, ed;
bool isGee = false;

void bfs() {
    while(!Cycles.empty()) {
        int now = Cycles.front();
        Cycles.pop();

        if(visited[now]) continue;
        visited[now] = true;

        if(now == ed){
            //도착점까지의 경로가 존재하면
            isGee = true;
            break;
        }

        for(auto next : Edge[now]) {
            if(!visited[next]) Cycles.push(next);
        }
    }
}

void bellman_ford() {
    Dist[st] = -Earn[st];

    for(int i = 0; i < N; i++) {
        for(auto edge : Edges) {
            int from = get<0>(edge);
            int to = get<1>(edge);
            ll cost = get<2>(edge);

            if(Dist[from] != INF && Dist[to] > Dist[from] + cost) {
                //현재 간선을 통해서 가는 것이 더 유리하면 갱신
                Dist[to] = Dist[from] + cost;
                if(i == N - 1) {
                    //음수 사이클 발생
                    Cycles.push(from);
                }

            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> st >> ed >> M;

    int u, v;
    ll w;
    for(int i = 1; i<=M; i++) {
        cin >> u >> v >> w;
        Edges.push_back({u, v, w});
        Edge[u].push_back(v);
    }
    
    for(int i = 0; i < N; i++) {
        cin >> Earn[i];
    }

    for(int i = 0; i < Edges.size(); i++) {
        auto edge = Edges[i];
        
        int from = get<0>(edge);
        int to = get<1>(edge);
        ll cost = get<2>(edge);

        //최단경로 알고리즘을 사용할 것이기 때문에 음수면 돈을 버는 것임
        cost -= Earn[to];

        Edges[i] = {from, to, cost};
    }

    bellman_ford();

    if(Dist[ed] == INF) {
        //도달 불가
        cout << "gg\n";
    }
    else {
        //도달 가능
        if(Cycles.size() > 0) {
            //사이클 존재
            //오민식에게 유리한 음수 사이클인지 확인
            bfs();
            if(isGee) cout << "Gee\n";
            else cout << -Dist[ed] << "\n";
        }
        else cout << -Dist[ed] << "\n";
    }
    return 0;
}