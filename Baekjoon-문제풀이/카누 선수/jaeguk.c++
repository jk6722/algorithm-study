#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 1000 + 5;
int T;
int K, N;
int weight[4][MAX_N];

vector<int> sum_01; // 0, 1반의 몸무게 합
vector<int> sum_23; // 2, 3반의 몸무게 합

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;

    while (T--) {
        cin >> K >> N;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < N; j++) {
                cin >> weight[i][j];
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                sum_01.push_back(weight[0][i] + weight[1][j]);
                sum_23.push_back(weight[2][i] + weight[3][j]);
            }
        }

        sort(sum_01.begin(), sum_01.end());
        sort(sum_23.begin(), sum_23.end());

        int ans = sum_01[0] + sum_23[0];
        // K에 가장 근사하는 조합 선정
        for (auto it : sum_01) {
            int idx = lower_bound(sum_23.begin(), sum_23.end(), (K - it)) - sum_23.begin();

            if (idx < N*N) {
                int prev_gap = abs(K - ans);
                int gap = abs(K - (it + sum_23[idx]));

                if (prev_gap >= gap) {
                    ans = prev_gap == gap ? min(ans, it + sum_23[idx]) : it + sum_23[idx];
                    prev_gap = gap; // prev_gap 변경
                }
                if (idx != 0 && (prev_gap >= abs(K - (it + sum_23[idx - 1])))) {
                    // 찾은 값 이전 값도 확인 (작은 쪽으로 근사할 수도 있으니까)
                    ans = prev_gap == abs(K - (it + sum_23[idx - 1])) ? min(ans, it + sum_23[idx - 1]) : it + sum_23[idx - 1];
                }
            }
            else {
                // lower_bound로 찾지 못했을시
                int prev_gap = abs(K - ans);
                int gap = abs(K - (it + sum_23[N * N - 1]));
                if (prev_gap >= gap)
                    ans = prev_gap == gap ? min(ans, it + sum_23[N * N - 1]) : it + sum_23[N * N -1];
            }
        }

        cout << ans << "\n";
        sum_01.clear();
        sum_23.clear();
    }
    return 0;
}