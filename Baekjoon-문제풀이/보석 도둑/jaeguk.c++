#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 300000 + 5;
int N, K;
multiset<int> bag;
vector<pair<int, ll>> jewely;

bool comp(pair<int, ll>& p1, pair<int, ll>& p2) {
    if (p1.first == p2.first) return p1.second < p2.second; // 가치가 같으면 가벼운 게 앞으로
    return p1.first > p2.first; // 가치가 높은 게 앞으로
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;

    ll M, V;
    for (int i = 0; i < N; i++) {
        cin >> M >> V;
        jewely.push_back({ V,M });
    }

    ll C;
    for (int i = 0; i < K; i++) {
        cin >> C;
        bag.insert(C);
    }

    sort(jewely.begin(), jewely.end(), comp);

    ll ans = 0;
    int empty_bag = K;

    for(auto jewel : jewely) { 
        int value = jewel.first;
        int weight = jewel.second;

        auto low_it = bag.lower_bound(weight);

        if (low_it != bag.end()) {
            // 만약 넣을 가방이 있으면
            ans += value;
            bag.erase(low_it);
            empty_bag--;
        }

        // 가방 자체가 없으면 중단
        if (!empty_bag) break;
    }

    cout << ans << "\n";

    return 0;
}