#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

string str;

int get_cnt() {
	int left_cnt = 0; // (
	int right_cnt = 0; // )
	int sum = 0;

	for(auto it : str) {
		if(it == '(') {
			left_cnt++;
			sum++;
		}
		if(it == ')') {
			right_cnt++;
			sum--;
		}
		if(sum < 0) {
			return right_cnt;
		}
	}
	return 0;
}

void reverse_str() {
	string n_str = "";
	for(int i = str.size() - 1; i >= 0; i--) {
		if(str[i] == '(') n_str += ')';
		else n_str += '(';
	}
	str = n_str;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> str;

	int ans = 0;
	ans += get_cnt();
	reverse_str();
	ans += get_cnt();
	cout << ans << "\n";

	return 0;
}