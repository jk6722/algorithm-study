#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Road {
    ll ticket; // 티켓 탑승
    ll ic; // IC 탑승
    ll card; // 카드비용
};

const int MAX_N = 100000 + 5;
Road road[MAX_N]; //각 도로에 대한 정보
int cnt[MAX_N]; //각 도로를 몇번 지났는지
int N, M;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    int prevP, p;
    cin >> prevP;
    for(int i = 1; i <= M - 1; i++) {
        cin >> p;
        cnt[min(p, prevP)]++;
        cnt[max(p, prevP)]--;
        prevP = p;
    }

    int a, b, c;
    for(int i = 1; i <= N-1; i++) {
        cin >> a >> b >> c;
        road[i] = {a, b, c};
    }

    for(int i = 1; i <= N; i++) {
        //누적합으로 도로를 지나간 횟수 구하기
        cnt[i] += cnt[i - 1];
    }

    ll ans = 0;
    for(int i = 1; i <= N-1; i++) {
        //각 도로에 대해서 최소비용 구하기
        ans += min(road[i].ticket * cnt[i], road[i].ic * cnt[i] + road[i].card);
    }

    cout << ans << "\n";

    return 0;
}