#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int R, C;
int Paper;
int M; // 잘못 칠해진 칸의 수
vector<pair<int, int>> missed;

bool comp(pair<int,int> p1, pair<int,int> p2) {
    return p1.second < p2.second;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    cin >> Paper;
    cin >> M;
    int y, x;
    int Left = 1, Right = max(R,C);
    for (int i = 0; i < M; i++) {
        cin >> y >> x;
        missed.push_back({ y,x });
        Left = max(y, Left);
    }
    // 무조건 밑변에 붙여야 하기 때문에 길이의 최소값은 잘못 색칠한 칸의 높이의 최대값

    sort(missed.begin(), missed.end(), comp);
    int ans = max(R,C);

    while (Left < Right) {
        int Mid = (Left + Right) / 2;

        int now_x = 0;
        int needed = 0;
        for (auto it : missed) {
            if (needed > Paper) break;
            if (it.second > now_x) {
                needed++;
                now_x = it.second + Mid - 1;
            }
        }

        if (needed > Paper) {
            Left++;
        }
        else {
            Right--;
            ans = min(ans, Mid);
        };
    }

    cout << ans << "\n";

    return 0;
}