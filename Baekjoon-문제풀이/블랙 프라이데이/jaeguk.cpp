#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;

const int MAX_N = 5000 + 5;
int arr[MAX_N];
int N, C;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> C;
	bool chk = false;
	for(int i = 0; i < N; i++) {
		cin >> arr[i];
		if(arr[i] == C) chk = true;
	}

	if(chk) {
		cout << 1 << "\n";
		return 0;
	}

	sort(arr, arr + N);

	for(int i = 0; i < N; i++) {
		int to_find = C - arr[i];

		int L = i + 1, R = N - 1;
		while(L < R) {
			int sum = arr[L] + arr[R];
			if(sum == to_find) goto success;
			if(arr[L] == to_find || arr[R] == to_find) goto success;

			if(sum < to_find) {
				// 합을 더 키워야 함
				L++;
			}
			if(sum > to_find) {
				// 합을 더 줄어야 함
				R--;
			}
		}
	}

	cout << 0 << "\n";
	return 0;

	success:
	cout << 1 << "\n";

	return 0;
}