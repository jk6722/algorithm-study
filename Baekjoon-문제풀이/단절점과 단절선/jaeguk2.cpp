#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
vector<int> Edge[MAX_N];
vector<pair<int,int>> Edges;
int N;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    int a, b;
    for(int i = 1; i < N; i++) {
        cin >> a >> b;
        Edge[a].push_back(b);
        Edge[b].push_back(a);
    }

    int q, t, k;
    cin >> q;

    for(int i = 1; i <= q; i++) {
        cin >> t >> k;
        if(t == 1) {
            //단절점인지?
            string ans = Edge[k].size() > 1 ? "yes" : "no";
            cout << ans << '\n';
        }
        else if(t == 2) {
            //단절선인지?
            cout << "yes\n";
        }
    }

    return 0;
}