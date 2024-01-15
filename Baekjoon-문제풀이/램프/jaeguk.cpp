#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 50 + 5;
string lamp[MAX_N];
int off[MAX_N]; // 행별로 꺼진 램프 수
int N, M, K;

bool isSame(int rowA, int rowB) {
    bool ret = lamp[rowA] == lamp[rowB] ? true : false;
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        int cnt = 0;
        cin >> lamp[i];
        for (int j = 0; j < M; j++) {
            if (lamp[i][j] == '0') cnt++;
        }
        off[i] = cnt;
    }

    cin >> K;

    int ans = 0;
    for (int row = 0; row < N; row++) {
        if (off[row] <= K && (K % 2 == off[row] % 2)) {
            // 모두 켤 수 있는 행
            int sameRow = 1;
            for (int j = row + 1; j < N; j++) {
                if (isSame(row, j)) {
                    sameRow++;
                }
            }
            ans = max(ans, sameRow);
        }
    }

    cout << ans << "\n";
    return 0;
}