#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
using pii = pair<int,int>;

void hanoi_order(int from, int mid, int to, int n) {
	if(n == 1) cout << from << " " << to << "\n";
	else {
		hanoi_order(from, to, mid, n - 1);
		cout << from << " " << to << "\n";
		hanoi_order(mid, from, to, n - 1);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int N;
	cin >> N;

	cout << (1 << N) - 1 << "\n";
	hanoi_order(1, 2, 3, N);

	return 0;
}