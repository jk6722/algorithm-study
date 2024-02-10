#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
int N, K;
int sum[MAX_N];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> sum[i];
        sum[i] += sum[i-1];
    }

    int L = 0, R = sum[N];

    int ans = 0;
    while(L <= R) {
        int mid = (L + R) / 2; //최솟값이 mid를 넘게 만들 수 있는가?
        int cnt = 0;
        int idx = 0;
        for(int i = 1; i <= N; i++) {
            if(sum[i] - sum[idx] >= mid) {
                cnt++;
                idx = i;
            }
        }

        if(cnt >= K) {
            ans = max(ans, mid);
            L = mid + 1;
        }
        else {
            R = mid - 1;
        }
    }

    cout << ans << "\n";
    return 0;
}