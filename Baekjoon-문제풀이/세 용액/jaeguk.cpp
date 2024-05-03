#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tiii = tuple<int,int,int>;

const int MAX_N = 5000 + 5;
const ll INF = LLONG_MAX;
int solution[MAX_N]; //용액
int N;

int bsearch(int l, int r, ll to_find) {
	if(l == r) return l;

	ll prev_min = INF;
	int idx = (l + r) / 2;

	while(l < r) {
		int mid = (l + r) / 2;

		if((ll)solution[mid] == to_find) return mid;

		if(abs(solution[mid] - to_find) < prev_min) {
			prev_min = abs(solution[mid] - (ll)to_find);
			idx = mid;
		}

		if((ll)solution[mid] < to_find) {
			l = mid + 1;
		}
		else if((ll)solution[mid] > to_find) {
			r = mid - 1;
		}
	}

	return idx;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> solution[i];
	}

	sort(solution, solution + N);

	tiii ans = {0, 0, 0};
	ll min_gap = INF;

	for(int i = 0; i < N - 2; i++) {
		for(int j = i + 1; j < N - 1; j++) {
			ll two_solution = (ll)solution[i] + (ll)solution[j]; // 두 용액의 합
			ll to_find = -two_solution; // 찾아야 하는 용액

			int idx = bsearch(j + 1, N, to_find);

			if(abs(two_solution + (ll)solution[idx]) < min_gap) {
				min_gap = abs(two_solution + (ll)solution[idx]);
				ans = {solution[i], solution[j], solution[idx]};
			}
			if(idx - 1 != j && abs(two_solution + (ll)solution[idx - 1]) < min_gap) {
				min_gap = abs(two_solution + (ll)solution[idx - 1]);
				ans = {solution[i], solution[j], solution[idx - 1]};
			}
			if(idx + 1 != N && abs(two_solution + (ll)solution[idx + 1]) < min_gap) {
				min_gap = abs(two_solution + (ll)solution[idx + 1]);
				ans = {solution[i], solution[j], solution[idx + 1]};
			}
		}
	}

	auto [a, b, c] = ans;
	cout << a << " " << b << " " << c << "\n";

	return 0;
}