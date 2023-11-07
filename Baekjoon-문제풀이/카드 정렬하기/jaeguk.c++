#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
int N;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    priority_queue<int, vector<int>, greater<int>> pq;
    cin >> N;
    int card;
    for (int i = 0; i < N; i++) {
        cin >> card;
        pq.push(card);
    }

    int ans = 0;
    while (pq.size() > 1) {
        int c1 = pq.top();
        pq.pop();
        int c2 = pq.top();
        pq.pop();
        
        int new_card = c1 + c2;
        ans += new_card;
        pq.push(new_card);
    }

    cout << ans << "\n";
    return 0;
}