#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 1000000 + 5;
int parent[MAX_N];
int T, n, k, m;

int Find(int x) {
    if(parent[x] == x) return x;
    return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    int parent_x = Find(x);
    int parent_y = Find(y);

    parent[parent_x] = parent_y;
}

void init() {
    for(int i = 1; i <= n; i++) {
        parent[i] = i;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> n >> k;
        init();
        
        int u, v;
        for(int i = 1; i<=k; i++) {
            cin >> u >> v;
            int parent_u = Find(u);
            int parent_v = Find(v);

            if(parent_u != parent_v)
                Union(parent_u, parent_v);
        }

        cin >> m;
        cout << "Scenario " << t << ":\n";
        for(int i = 1; i <= m; i++) {
            cin >> u >> v;
            if(Find(u) != Find(v)) cout << "0\n";
            else cout << "1\n";
        }
        cout << "\n";
    }

    return 0;
}