#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100 + 5;
const int MAX_K = 100000 + 5;
const int mINF = -1000000 * 100 - 1;
int DP[MAX_N][2][MAX_K]; // [구간][도보 or 자전거][시간]
int N, K;
pair<int,int> amountRaised[MAX_N][2];

void init() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            DP[i][0][j] = mINF;
            DP[i][1][j] = mINF;
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    init();
    int time1, raise1, time2, raise2;
    for (int i = 1; i <= N; i++) {
        cin >> time1 >> raise1 >> time2 >> raise2;
        amountRaised[i][0] = { time1, raise1 }; //도보
        amountRaised[i][1] = { time2, raise2 }; //자전거
    }

    DP[0][0][0] = 0;
    DP[0][1][0] = 0;

    pair<int, int> walk, bicycle;
    for (int i = 1; i <= N; i++) {
        walk = amountRaised[i][0];
        bicycle = amountRaised[i][1];

        for(int t = min(walk.first, bicycle.first); t <= K; t++) {
            int preWalkTime = t - walk.first; // 걸어온 경우 출발 시간
            int preBicycleTime = t - bicycle.first; // 자전거를 타고 온 경우 출발 시간

            if (preWalkTime >= 0) {
                DP[i][0][t] = max(DP[i - 1][0][preWalkTime], DP[i - 1][1][preWalkTime]) + walk.second;
            }
            if (preBicycleTime >= 0) {
                DP[i][1][t] = max(DP[i - 1][0][preBicycleTime], DP[i - 1][1][preBicycleTime]) + bicycle.second;
            }
        }
    }

    int ans = 0;
    for (int t = 0; t <= K; t++) {
        ans = max(ans, max(DP[N][0][t], DP[N][1][t]));
    }

    cout << ans << "\n";
    return 0;
}