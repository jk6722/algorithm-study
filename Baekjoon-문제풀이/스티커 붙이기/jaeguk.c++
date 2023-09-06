#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 40 + 5;
int N, M, K;

bool Sticker[100][MAX_N][MAX_N];
vector<pair<int, int>> Size;
bool Monitor[MAX_N][MAX_N];

void rotateSticker(int sticker_num) {
	// 스티커 시계방향으로 90도 회전

	bool PrevSticker[MAX_N][MAX_N];
	memset(PrevSticker, false, sizeof(PrevSticker));

	int row_size = Size[sticker_num].first;
	int col_size = Size[sticker_num].second;

	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			PrevSticker[i][j] = Sticker[sticker_num][i][j];

	memset(Sticker[sticker_num], false, sizeof(Sticker[sticker_num]));

	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			Sticker[sticker_num][j][row_size - i - 1] = PrevSticker[i][j];
}

bool isOk(int sticker_num, int row_st, int col_st) {
	int row_size = Size[sticker_num].first;
	int col_size = Size[sticker_num].second;

	bool chk = true;

 	if (row_st + row_size > N || col_st + col_size > M) { // 스티커가 모니터를 넘어가면
		return false;
	}

	for (int i = 0; i < row_size ; i++) {
		if (!chk) break;
		for (int j = 0; j < col_size; j++) {
			if (!Sticker[sticker_num][i][j]) continue;
			if (Monitor[row_st + i][col_st + j]) {
				chk = false;
				break;
			}
		}
	}
	if (chk) return true;
	return false;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++) {
		int R, C;
		cin >> R >> C;
		Size.push_back({ R,C });
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				cin >> Sticker[i][j][k];
			}
		}
	}

	int ans = 0;

	for (int sticker = 0; sticker < K; sticker++) {
		for (int turn = 0; turn < 4; turn++) {
			int row_size = Size[sticker].first;
			int col_size = Size[sticker].second;

			bool chk = false;
			for (int i = 0; i < N; i++) {
				if (chk) break;
				for (int j = 0; j < M; j++) {
					if (!chk && isOk(sticker, i, j)) {
						// 모니터에 스티커 붙이는 작업
						for (int p = 0; p < row_size; p++) {
							for (int l = 0; l < col_size; l++) {
								if (!Sticker[sticker][p][l]) continue;
								Monitor[i + p][j + l] = Sticker[sticker][p][l];
								ans++;
							}
						}
						chk = true;
						break;
					}
				}
			}

			if (chk) break;

			if (turn != 3) {
				rotateSticker(sticker);
				Size[sticker].first = col_size;
				Size[sticker].second = row_size;
			}
		}
	}

	cout << ans << "\n";
	return 0;
}