#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1024 + 5;
int people[MAX_N][MAX_N];
int sum[MAX_N][MAX_N]; // (1,1) ~ (i,j) 누적합
int K, N, M;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> people[i][j];
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            // 누적합 계산
            sum[i][j] = people[i][j] + sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
        }
    }

    cin >> K;
    int y1, x1, y2, x2;

    while (K--) {
        cin >> y1 >> x1 >> y2 >> x2;
        cout << sum[y2][x2] - sum[y2][x1 - 1] - sum[y1 - 1][x2] + sum[y1 - 1][x1 - 1] << "\n";
    }
    return 0;
}