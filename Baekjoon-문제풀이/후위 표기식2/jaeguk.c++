#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

stack<double> S;
string str;
const int MAX_N = 26 + 1;
int table[MAX_N] = {0};
int N;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    cin >> str;

    for (int i = 0; i < N; i++) {
        cin >> table[i];
    }

    for (int i = 0; i < str.length(); i++) {
        char op = str[i];
        if (op == '*' || op == '/' || op == '+' || op == '-') {
            // 연산자이면
            double sub2 = S.top();
            S.pop();
            double sub1 = S.top();
            S.pop();

            double res = 0.0;

            switch (op) {
                case '*':
                    res = (double)sub1 * sub2;
                    break;
                case '/':
                    res = (double)sub1 / sub2;
                    break;
                case '+':
                    res = (double)sub1 + sub2;
                    break;
                case '-':
                    res = (double)sub1 - sub2;
                    break;
            }

            S.push(res);
        }
        else {
            S.push((double)table[op - 'A']);
        }
    }

    cout << fixed;
    cout.precision(2);
    cout << S.top() << "\n";

    return 0;
}