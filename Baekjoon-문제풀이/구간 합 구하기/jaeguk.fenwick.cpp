#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;
typedef long long ll;

const int MAX_N = 1000000 + 5;
int N, M, K;

//Fenwick Tree (펜윅 트리)
ll tree[MAX_N], arr[MAX_N];

void update(int idx, ll value) {
	while (idx <= N) {
		tree[idx] += value;
		// & 연산자 사용해서 인덱스 업데이트
		// bit가 1인 자리 중에 가장 낮은 자리의 1을 찾는 방법
		idx += idx & -idx;
	}
}

ll query(int idx) {
	ll sum = 0;

	while (idx > 0) {
		sum += tree[idx];
		idx -= idx & -idx;
	}
	return sum;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
		update(i, arr[i]);
	}

	int a, b;
	ll c, diff;
	for (int i = 1; i <= M + K; i++) {
		cin >> a >> b >> c;
		switch (a) {
		case 1:
			//변경
			diff = c - arr[b];
			arr[b] = c;
			update(b, diff);
			break;
		case 2:
			cout << query(c) - query(b - 1) << "\n";
			break;
		}
	}

	return 0;
}