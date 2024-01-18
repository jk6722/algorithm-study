#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAX_N = 1000000 + 5;
ll sum[MAX_N];
int N, K, Q;

ll cmd[MAX_N];
set<int> cmds;

void something(ll cnt, int jump) {
    int i = 0;
    while (i < N) {
        sum[i] += cnt;
        i += jump;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> K;

    int X;
    for (int i = 0; i < K; i++) {
        // K번의 명령
        cin >> X;
        cmds.insert(X);
        cmd[X]++;
    }
    
    for (auto it : cmds) {
        // 명령 수행
        ll cnt = cmd[it];
        something(cnt, it);
    }

    for (int i = 1; i < N; i++) {
        sum[i] += sum[i - 1];
    }

    cin >> Q;
    int L, R;
    for (int i = 0; i < Q; i++) {
        cin >> L >> R;
        cout << sum[R] - sum[L - 1] << "\n";
    }

    return 0;
}