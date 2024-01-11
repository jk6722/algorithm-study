#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using apq = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>; // 오름차순 pq
using dpq = priority_queue<pair<int, int>>; // 내림차순 pq

const int MAX_N = 1000000 + 5;
int T, K;
bool isRemain[MAX_N]; // i번째로 Insert된 숫자가 제거되었는지 여부

void sync_queue(apq* asc_pq, dpq* desc_pq) {
    while (!desc_pq->empty()) {
        pair<int, int> now = desc_pq->top();
        if (isRemain[now.second]) break;
        // 이미 빠진 숫자는 pop
        desc_pq->pop();
    }
    while (!asc_pq->empty()) {
        pair<int, int> now = asc_pq->top();
        if (isRemain[now.second]) break;
        // 이미 빠진 숫자는 pop
        asc_pq->pop();
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        memset(isRemain, 0, sizeof(isRemain));
        cin >> K;
        char cmd;
        int num;

        apq asc_pq;
        dpq desc_pq;

        for (int i = 0; i < K; i++) {
            cin >> cmd >> num;

            switch (cmd) {
            case 'I':
                asc_pq.push({num, i});
                desc_pq.push({num, i});
                isRemain[i] = true;
                break;
            case 'D':
                sync_queue(&asc_pq, &desc_pq);
                if (num == 1) {
                    // 가장 큰 수 pop
                    if (!desc_pq.empty()) {
                        pair<int,int> tmp = desc_pq.top();
                        isRemain[tmp.second] = false;
                        desc_pq.pop();
                    }
                }
                else if (num == -1) {
                    // 가장 작은 수 pop
                    if (!asc_pq.empty()) {
                        pair<int, int> tmp = asc_pq.top();
                        isRemain[tmp.second] = false;
                        asc_pq.pop();
                    }
                }
            }
        }
        sync_queue(&asc_pq, &desc_pq);
        if (desc_pq.empty()) {
            cout << "EMPTY\n";
        }
        else {
            cout << desc_pq.top().first << " " << asc_pq.top().first << "\n";
        }
    }

    return 0;
}