#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = long long;

int T;
string str;

void isPalindrome(int L, int R, int& ans, bool isRemoved) {
    if (L >= R) {
        ans = min(ans, isRemoved ? 1 : 0);
        return;
    }

    if (str[L] == str[R]) {
        isPalindrome(L + 1, R - 1, ans, isRemoved);
    }
    if (str[L + 1] == str[R] && !isRemoved) {
        // 왼쪽 글자를 버리면 팰린드롬 가능성이 있다면
        isPalindrome(L + 1, R, ans, true);
        isRemoved = false;
    }
    if (str[L] == str[R - 1] && !isRemoved) {
        // 오른쪽 글자를 버리면 팰린드롬 가능성이 있다면
        isPalindrome(L, R - 1, ans, true);
        isRemoved = false;
    }
    else {
        ans = min(ans, 2);
        return;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;

    while (T--) {
        int ans = 3;
        cin >> str;
        isPalindrome(0, str.length() - 1, ans, false);
        cout << ans << "\n";
    }

    return 0;
}