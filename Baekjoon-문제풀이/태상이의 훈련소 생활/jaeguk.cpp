#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 100000 + 5;
int N, M;
int ground[MAX_N];
int command[MAX_N];


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        cin >> ground[i];
    }

    int from, to, height;
    for (int i = 1; i <= M; i++) {
        cin >> from >> to >> height;
        command[from] += height;
        command[to + 1] -= height;
    }

    for (int i = 1; i <= N; i++) {
        command[i] += command[i - 1];
        ground[i] += command[i];
    }

    for (int i = 1; i <= N; i++) {
        cout << ground[i] << " ";
    }
    cout << "\n";

    return 0;
}