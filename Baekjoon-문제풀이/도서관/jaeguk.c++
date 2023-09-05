#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, M;

vector<int> Book_Negative;
vector<int> Book_Positive;


int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		int location;
		cin >> location;
		location < 0 ? Book_Negative.push_back(location) : Book_Positive.push_back(location);
	}

	sort(Book_Negative.begin(), Book_Negative.end());
	sort(Book_Positive.begin(), Book_Positive.end(), greater<int>());

	int pointer_n = 0;
	int pointer_p = 0;

	int ans = 0;

	int pos_max = Book_Positive.size() == 0 ? -1 : Book_Positive[0];
	int neg_max = Book_Negative.size() == 0 ? -1 : abs(Book_Negative[0]);

	bool isNegativeLast = neg_max > pos_max ? true : false;

	// 양수 방향 마지막에
	if (!isNegativeLast) {
		ans += Book_Positive[0];
		for (int i = 0; i < M; i++) {
			Book_Positive.erase(Book_Positive.begin());
			if (Book_Positive.size() == 0) break;
		}
	}
	// 음수 방향 마지막에
	else if (isNegativeLast) {
		ans += abs(Book_Negative[0]);
		for (int i = 0; i < M; i++) {
			Book_Negative.erase(Book_Negative.begin());
			if (Book_Negative.size() == 0) break;
		}
	}

	while (pointer_n < Book_Negative.size()) {
		ans += abs(Book_Negative[pointer_n]) * 2;
		pointer_n += M;
	}

	while(pointer_p < Book_Positive.size()) {
		ans += Book_Positive[pointer_p] * 2;
		pointer_p += M;
	}

	cout << ans << "\n";


	return 0;
}