#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
int G, P;
bool visited[MAX_N];
vector<int> mem(MAX_N);

bool docking(int st) {
    int i = mem[st] != MAX_N ? mem[st] : st;
    // 기록된 값을 이용해서 i 갱신
    for (i; i >= 1; i = min(i - 1, mem[i])) {
        if (visited[i]) continue;
        else {
            visited[i] = true;
            mem[st] = i - 1;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fill(mem.begin(), mem.end(), MAX_N);

    cin >> G >> P;
    int g;
    int ans = 0;
    bool chk = false;
    for (int i = 1; i <= P; i++) {
        cin >> g;
        if (!chk) {
            if (docking(g)) ans++;
            else chk = true;
        }
    }

    cout << ans << "\n";
    return 0;
}