#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int left, right;
const int MAX_N = 100000 + 5;
int dance[MAX_N];
const int INF = 987654321;
ll DP[5][5][MAX_N]; // DP[왼발][오른발][단계]

int getStrength(int now, int next) {
    // now -> next로 발을 움직일 때 얼마의 힘이 드는지
    int gap = abs(now - next);
    if (now == 0) return 2;
    else if (!gap) return 1;
    else if (gap == 1 || gap == 3) return 3;
    else return 4;
}

ll getLeftDP(int next, int right, int i) {
    ll ret = INF;
    for (int prev = 0; prev < 5; prev++) {
        ret = min(DP[prev][right][i - 1] + getStrength(prev, next), ret);
    }
    return ret;
}

ll getRightDP(int next, int left, int i) {
    ll ret = INF;
    for (int prev = 0; prev < 5; prev++) {
        ret = min(DP[left][prev][i - 1] + getStrength(prev, next), ret);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num = 0;
    int idx = 1;
    while (true) {
        cin >> num;
        if (!num) break;
        dance[idx++] = num;
    }

    // initialize
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < idx; k++)
                DP[i][j][k] = INF;
    DP[0][0][0] = 0;


    for (int i = 1; i < idx; i++) {
        // 다음에 움직여야 하는 칸
        int next = dance[i];

        // j는 움직이려는 발과 다른 쪽 발
        for (int j = 0; j < 5; j++) {
            if (next != 0 && j != 0 && next == j) continue; // 두 발이 같은 칸에 들어가는 경우
            // 왼발을 움직인 경우
            DP[next][j][i] = getLeftDP(next, j, i);
            // 오른발을 움직인 경우
            DP[j][next][i] = getRightDP(next, j, i);
        }
    }

    ll ans = INF;
    int last = dance[idx- 1];

    for (int i = 0; i < 5; i++)
        ans = min(DP[last][i][idx - 1], min(DP[i][last][idx - 1], ans));

    cout << ans << "\n";

    return 0;
}