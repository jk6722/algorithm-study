#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

const int MAX_N = 1000 + 5;
int board[MAX_N][MAX_N];
int DP[MAX_N][MAX_N];
int N;

bool is_ok(pii pos) {
	if(pos.first < 0 || pos.first >= N || pos.second < 0 || pos.second >= N) return false;
	return true;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	DP[0][0] = board[0][0] == 0 ? 1 : 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(is_ok({i - 1, j}) && is_ok({i, j - 1})) {
				// 위 왼쪽 모두 있는 경우

				int top_milk = DP[i - 1][j] % 3; //다음에 먹어야 하는 맛
				int left_milk = DP[i][j - 1] % 3;
				
				int top = top_milk == board[i][j] ? DP[i - 1][j] + 1 : DP[i - 1][j];
				int left = left_milk == board[i][j] ? DP[i][j - 1] + 1 : DP[i][j - 1];

				DP[i][j] = max(top, left);
			}
			else if(is_ok({i - 1, j})) {
				// 위만 있는 경우

				int top_milk = DP[i - 1][j] % 3;
				int top = top_milk == board[i][j] ? DP[i - 1][j] + 1 : DP[i - 1][j];

				DP[i][j] = top;
			}
			else if(is_ok({i, j - 1})) {
				// 왼쪽만 있는 경우

				int left_milk = DP[i][j - 1] % 3;
				int left = left_milk == board[i][j] ? DP[i][j - 1] + 1 : DP[i][j - 1];

				DP[i][j] = left;
			}
		}
	}

	cout << DP[N - 1][N - 1] << "\n";
	return 0;
}