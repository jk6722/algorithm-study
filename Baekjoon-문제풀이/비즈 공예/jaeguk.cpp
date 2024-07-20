#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;

const int MAX_N = 5 + 1; //최대 구슬 종류
const int MAX_M = 10 + 1; //각 구슬당 최대 개수
ll DP[MAX_M][MAX_M][MAX_M][MAX_M][MAX_M][MAX_N][MAX_N];
int marble[MAX_N];
int N, M;

ll solve(int depth, int prev, int pprev) {
	if(depth == M) return 1; //모든 구슬을 소비했다면
	
	ll &ret = DP[marble[1]][marble[2]][marble[3]][marble[4]][marble[5]][prev][pprev];
	if(ret != -1) return ret;

	ret = 0;
	for(int i = 1; i <= N; i++) {
		if(prev != i && pprev != i && marble[i]) {
			//i를 끼울 수 있다면
			marble[i]--;
			ret += solve(depth + 1, i, prev);
			marble[i]++;
		}
	}
	return ret;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for(int i = 1; i <= N; i++) {
		cin >> marble[i];
		M += marble[i];
	}

	memset(DP, -1, sizeof(DP));
	
	ll ans = solve(0, 0, 0);
	cout << ans << "\n";

	return 0;
}