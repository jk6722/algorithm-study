#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;

const int MAX_N = 100000 + 5;
int feeds[MAX_N]; //나뭇가지 위의 먹이
ll DP[MAX_N]; //최대 탈피 에너지
int N, K;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;
	for(int i = 1; i <= N; i++) {
		cin >> feeds[i];
	}

	int l = 1, r = 1;
	ll sum = (ll)feeds[l];

	while(r <= N) {
		DP[r] = max(DP[r], DP[r - 1]);

		if(sum >= K) {
			// 누적합이 만족도 이상인 경우
			DP[r] = max(DP[r], DP[l - 1] + (ll)(sum - K));

			if(l < r) {
				sum -= (ll)feeds[l++];
			}
			else if(l == r) {
				r++;
				l++;
				sum = (ll)feeds[r];
			}
		}
		else sum += (ll)feeds[++r];
	}

	cout << DP[N] << "\n";

	return 0;
}