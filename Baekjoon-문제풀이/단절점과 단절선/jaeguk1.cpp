#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
vector<int> Edge[MAX_N];
vector<pair<int,int>> Edges;
int visited[MAX_N]; //방문된 순서
int N;
int counter;

bool isCutVertex[MAX_N];
set<pair<int,int>> isCutEdge;

int findCutVertex(int now, bool isRoot) {
    visited[now] = ++counter; //정점 방문 순서
    int ret = visited[now];

    int child = 0; //자식노드 수 (루트일 경우 필요)
    
    for(auto next : Edge[now]) {
        if(visited[next]) {
            //이미 방문된 정점이라면
            ret = min(ret, visited[next]);
            continue;
        }
        child++;
        int prev = findCutVertex(next, false);
        /*
            현재 정점이 루트가 아니고,
            현재 정점을 거치지 않고, 현재 방문순서보다 더 빠른 방문순서를 가진 노드로 갈 수 없다면 현재 노드는 단절점
        */
        if(!isRoot && prev >= visited[now])
            isCutVertex[now] = true;

        ret = min(ret, prev);
    }
    /*
        현재 정점이 루트라면,
        자식 노드가 둘 이상이면 무조건 단절점
    */
    if(isRoot) isCutVertex[now] = child >= 2;

    return ret;
}

int findCutEdge(int now, int parent) {
    visited[now] = ++counter; //정점 방문 순서
    int ret = visited[now];

    for(auto next : Edge[now]) {
        if(next == parent) {
            // 현재 노드와 부모 노드 사이의 간선이면 패스
            continue;
        }

        if(visited[next]) {
            // 이미 방문된 정점이라면
            ret = min(ret, visited[next]);
            continue;
        }

        int prev = findCutEdge(next, now);

        /*
            현재 간선을 거치지 않고,
            현재 방문 순서보다 앞선 방문 순서를 가진 정점에 방문할 수 없다면 단절선
        */
        if(prev > visited[now]) {
            isCutEdge.insert({min(now, next), max(now, next)});
        }
        ret = min(ret, prev);
    }
    return ret;
}

void init() {
    counter = 0;
    memset(visited, 0, sizeof(visited));
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    int a, b;
    for(int i = 1; i < N; i++) {
        cin >> a >> b;
        Edge[a].push_back(b);
        Edge[b].push_back(a);
        Edges.push_back({min(a,b), max(a,b)});
    }

    for(int i = 1; i <= N; i++) {
        if(!visited[i]) findCutVertex(i, true);
    }

    init();
    for(int i = 1; i <= N; i++) {
        if(!visited[i]) findCutEdge(i, 0);
    }

    int q, t, k;
    cin >> q;

    for(int i = 1; i <= q; i++) {
        cin >> t >> k;

        if(t == 1) {
            //단절점인지?
            string ans = isCutVertex[k] ? "yes" : "no";
            cout << ans << "\n";
        }
        else if(t == 2) {
            //단절선인지?
            pair<int,int> edge = Edges[k-1];
            string ans = isCutEdge.count({edge.first, edge.second}) ? "yes" : "no";
            cout << ans << "\n";
        }
    }

    return 0;
}