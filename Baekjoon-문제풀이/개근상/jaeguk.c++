#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000
const int MAX_N = 1000000 + 5;
int N;

int DP[MAX_N][3][2][3]; // [O, A, L][지각한 횟수][연속 결석 수]

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    DP[0][0][0][0] = 1;

    for (int i = 1; i <= N; i++) {
        DP[i][0][0][0] = (DP[i - 1][0][0][0] + DP[i - 1][1][0][1] + DP[i - 1][1][0][2]) % MOD;
        DP[i][0][1][0] = (DP[i - 1][0][1][0] + DP[i - 1][1][1][1] + DP[i - 1][1][1][2] + DP[i - 1][2][1][0]) % MOD;

        DP[i][1][0][1] = DP[i - 1][0][0][0] % MOD;
        DP[i][1][0][2] = DP[i - 1][1][0][1] % MOD;
        DP[i][1][1][1] = (DP[i - 1][0][1][0] + DP[i - 1][2][1][0]) % MOD;
        DP[i][1][1][2] = (DP[i - 1][1][1][1]) % MOD;

        DP[i][2][1][0] = (DP[i - 1][0][0][0] + DP[i - 1][1][0][1] + DP[i - 1][1][0][2]) % MOD;
    }

    int ans = (DP[N][0][0][0] + DP[N][0][1][0] + DP[N][1][0][1] + DP[N][1][0][2] + DP[N][1][1][1] + DP[N][1][1][2] + DP[N][2][1][0]) % MOD;

    cout << ans << "\n";
    return 0;
}