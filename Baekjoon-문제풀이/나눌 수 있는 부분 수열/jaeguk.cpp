#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAX_N = 50000 + 5;
const int MAX_D = 1000000 + 5;
ll arr[MAX_N];
ll sum[MAX_N];
ll mod[MAX_D];
int c, d, n;


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> c;
    while (c--) {
        memset(arr, 0, sizeof(arr));
        memset(sum, 0, sizeof(sum));
        memset(mod, 0, sizeof(mod));

        cin >> d >> n;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            // 누적합 계산
            sum[i] = sum[i - 1] + arr[i];
            mod[sum[i] % d]++;
        }

        ll ans = mod[0]; // 누적합 자체가 나머지가 0인 경우

        for (int i = 0; i < d; i++) {
            if (mod[i] <= 1) continue;
            ans += (mod[i] * (mod[i] - 1) / 2LL); // 만들 수 있는 조합의 수
        }

        cout << ans << "\n";

    }

    return 0;
}