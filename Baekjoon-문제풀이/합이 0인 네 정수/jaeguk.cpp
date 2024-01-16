#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 4000 + 5;
int A[MAX_N];
int B[MAX_N];
int C[MAX_N];
int D[MAX_N];
int N;

vector<int> AB;
vector<int> CD;

int findSameNum(string cmd, int st) {
    int ret = 0;
    if (cmd == "AB") {
        int toFind = AB[st];
        for (int i = st; i < AB.size(); i++) {
            if (AB[i] == toFind) ret++;
            else break;
        }
    }
    else if (cmd == "CD") {
        int toFind = CD[st];
        for (int i = st; i >= 0; i--) {
            if (CD[i] == toFind) ret++;
            else break;
        }
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    int a, b, c, d;
    for (int i = 0; i < N; i++) {
        cin >> a >> b >> c >> d;
        A[i] = a;
        B[i] = b;
        C[i] = c;
        D[i] = d;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            AB.push_back(A[i] + B[j]);
            CD.push_back(C[i] + D[j]);
        }
    }
    sort(AB.begin(), AB.end());
    sort(CD.begin(), CD.end());

    int idx_AB = 0, idx_CD = CD.size() - 1;

    ll ans = 0;
    while (idx_AB < AB.size() && idx_CD >= 0) {
        ll ABCD = AB[idx_AB] + CD[idx_CD];
        if (ABCD == 0) {
            //합이 0이 되는 경우
            ll cnt_AB = findSameNum("AB", idx_AB);
            ll cnt_CD = findSameNum("CD", idx_CD);
            ans += (cnt_AB * cnt_CD);
            idx_AB += cnt_AB;
            idx_CD -= cnt_CD;
        }
        else if (ABCD > 0) {
            //합이 양수인 경우
            idx_CD--;
        }
        else if (ABCD < 0) {
            //합이 음수인 경우
            idx_AB++;
        }
    }

    cout << ans << "\n";
    return 0;
}