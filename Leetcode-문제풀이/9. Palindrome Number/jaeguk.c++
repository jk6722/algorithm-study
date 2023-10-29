#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        string str = to_string(x);
        reverse(str.begin(), str.end());
        int x_reverse = stoll(str);

        return x == x_reverse;
    }
};