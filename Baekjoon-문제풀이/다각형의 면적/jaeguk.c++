#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX_N = 10000 + 5;
ll x[MAX_N] = { 0 };
ll y[MAX_N] = { 0 };
int N;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++)
        cin >> x[i] >> y[i];

    x[N] = x[0];
    y[N] = y[0];

    ll ans = 0;

    for (int i = 0; i < N; i++) {
        ans += x[i] * y[i + 1];
        ans -= x[i + 1] * y[i];
    }

    cout << fixed;
    cout.precision(1);

    cout << round(abs((double)ans / 2) * 10) / 10 << "\n";
    return 0;
}