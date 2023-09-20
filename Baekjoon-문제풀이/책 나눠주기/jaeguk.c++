#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000 + 5;
int T;
int N, M;
vector<pair<int, int>> arr;
vector<bool> visited(MAX_N);

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second)
        return a.first < b.first;
    return a.second < b.second;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        fill(visited.begin(), visited.end(), false);

        cin >> N >> M;

        int a, b;
        for (int i = 0; i < M; i++) {
            cin >> a >> b;
            arr.push_back({ a,b });
        }
        sort(arr.begin(), arr.end(), comp);

        int ans = 0;
        for (auto it : arr) {
            for (int i = it.first; i <= it.second; i++) {
                if (!visited[i]) {
                    visited[i] = true;
                    ans++;
                    break;
                }
            }
        }
        cout << ans << "\n";
        arr.clear();
    }
    return 0;
}