#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 250000 + 5;
int N;
ll Room[MAX_N];
ll DP[2][2];

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> Room[i];

	ll ans = 0;

	// 1번에 개미를 안 넣는 경우
	DP[0][0] = Room[0];
	for (int i = 1; i < N; i++) {
		if (Room[i]) {
			DP[1][0] = max(DP[0][0], DP[0][1]) + Room[i];
			DP[1][1] = DP[0][1] + 1;
		}
		else {
			DP[1][0] = max(DP[0][0], DP[0][1]);
			DP[1][1] = DP[0][0] + 1;
		}
		DP[0][0] = DP[1][0];
		DP[0][1] = DP[1][1];
	}

	ans = max(DP[0][0], DP[0][1]);

	// 1번에 개미를 넣는 경우
	DP[0][0] = 1 + Room[1];
	DP[0][1] = 1 + Room[1];
	for (int i = 2; i < N - 1; i++) {
		if (Room[i]) {
			DP[1][0] = max(DP[0][0], DP[0][1]) + Room[i];
			DP[1][1] = DP[0][1] + 1;
		}
		else {
			DP[1][0] = max(DP[0][0], DP[0][1]);
			DP[1][1] = DP[0][0] + 1;
		}
		DP[0][0] = DP[1][0];
		DP[0][1] = DP[1][1];
	}

	if (N == 2)
		ans = max(ans, max(DP[0][0], DP[0][1]));
	else
		ans = max(ans, max(DP[0][0], DP[0][1]) + Room[N-1]);

	cout << ans << "\n";

	return 0;
}