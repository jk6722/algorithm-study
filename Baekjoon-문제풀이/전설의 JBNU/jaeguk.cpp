#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
unordered_map<int, int> JBNU;

set<int> keys;
set<int> negKeys;

int N, M, K;

int findNearKey(int key) {
    auto upper = keys.lower_bound(key);
    auto lower = negKeys.lower_bound(-key);

    if (upper != keys.end() && lower != negKeys.end()) {
        int upper_gap = abs(*upper - key);
        int lower_gap = abs(-*lower - key);

        if (upper_gap > K && lower_gap > K) {
            return -1;
        }

        if (upper_gap == lower_gap) {
            if (-*lower == *upper)
                return *upper;
            else return -2;
        }
        else if (upper_gap > lower_gap) {
            return -*lower;
        }
        else if (upper_gap < lower_gap) {
            return *upper;
        }
    }
    else if (upper != keys.end()) {
        int upper_gap = abs(*upper - key);
        if (upper_gap > K) return -1;
        else return *upper;
    }
    else if (lower != negKeys.end()) {
        int lower_gap = abs(-*lower - key);
        if (lower_gap > K) return -1;
        return -*lower;
    }
    else return -1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;

    int key, value;
    for (int i = 1; i <= N; i++) {
        cin >> key >> value;
        JBNU.insert({ key, value });
        keys.insert(key);
        negKeys.insert(-key);
    }

    int cmd;
    int nearKey;
    for (int i = 1; i <= M; i++) {
        cin >> cmd;
        switch (cmd) {
        case 1:
            // 데이터 추가
            cin >> key >> value;
            JBNU.insert({ key, value });
            keys.insert(key);
            negKeys.insert(-key);
            break;
        case 2:
            // 데이터 변경
            cin >> key >> value;
            nearKey = findNearKey(key);
            if (nearKey >= 0) {
                JBNU[nearKey] = value;
            }
            break;
        case 3:
            // 데이터 탐색
            cin >> key;
            nearKey = findNearKey(key);
            if (nearKey == -1) {
                // 만족하는 키 없음
                cout << nearKey << "\n";
            }
            else if (nearKey == -2) {
                cout << "?\n";
            }
            else cout << JBNU[nearKey] << "\n";
            break;
        }
    }

    return 0;
}