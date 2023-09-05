#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
int N, K;
int ans = 0;

bool isTaught[26];
string words[50 + 5];

void checkAndCount(void) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		bool chk = true;
		for (int j = 0; j < words[i].length(); j++) {
			if (!isTaught[words[i][j] - 'a']) {
				chk = false;
				break;
			}
		}
		if (chk) count++;
	}
	ans = max(ans, count);
}

void backtracking(int depth, int prevIndex) {
	if (depth == K) {
		// check
		checkAndCount();
		return;
	}
	for (int i = prevIndex + 1; i < 26; i++) {
		if (!isTaught[i]) {
			isTaught[i] = true;
			backtracking(depth + 1, i);
			isTaught[i] = false;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		cin >> words[i];
	}

	if (K < 5) {
		cout << 0 << "\n";
		return 0;
	}
	
	isTaught['a' - 'a'] = true;
	isTaught['n' - 'a'] = true;
	isTaught['t' - 'a'] = true;
	isTaught['i' - 'a'] = true;
	isTaught['c' - 'a'] = true;

	backtracking(5, 0);

	cout << ans << "\n";

	return 0;
}