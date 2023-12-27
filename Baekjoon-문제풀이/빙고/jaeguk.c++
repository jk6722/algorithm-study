#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
int N, M;

int bingo[6][6];
int bingo_count = 0;

bool check(int i, int j) {
    int prev_bingo_count = bingo_count;

    // 세로줄 확인
    bool ret = true;
    for (int row = 0; row < 5; row++) {
        if (bingo[row][j]) ret = false;
    }
    if (ret) bingo_count++;

    // 가로줄 확인
    ret = true;
    for (int col = 0; col < 5; col++) {
        if (bingo[i][col]) ret = false;
    }
    if (ret) bingo_count++;

    if (i == j) {
        // 우하향 대각선 확인
        ret = true;
        for (int iter = 0; iter < 5; iter++) {
            if (bingo[iter][iter]) ret = false;
        }
        if (ret) bingo_count++;

    }

    if (i + j == 4) {
        // 좌하향 대각선 확인
        ret = true;
        for (int iter = 0; iter < 5; iter++) {
            if (bingo[iter][4 - iter]) ret = false;
        }
        if (ret) bingo_count++;
    }

    // 새로운 빙고가 발견되었으면
    if (prev_bingo_count < bingo_count) return true;
    return false;
}

pair<int,int> find(int num) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (bingo[i][j] == num) {
                bingo[i][j] = 0;
                return {i, j};
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cin >> bingo[i][j];

    int num;
    int ans = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> num;
            pair<int,int> pos = find(num);
            ans++;
            bool res = check(pos.first, pos.second);
            if (res && bingo_count >= 3) {
                cout << ans << "\n";
                return 0;
            }
        }
    }
    return 0;
}