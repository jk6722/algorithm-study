#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 1000 + 5;
int m, n, order;
int A[MAX_N];
int B[MAX_N];
int SumA[MAX_N];
int SumB[MAX_N];

vector<int> PizzaA;
vector<int> PizzaB;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> order;
    cin >> m >> n;

    for (int i = 1; i <= m; i++)
        cin >> A[i];
    for (int i = 1; i <= n; i++)
        cin >> B[i];

    // 누적합 계산
    for (int i = 1; i <= m; i++) {
        SumA[i] = SumA[i - 1] + A[i];
    }
    for (int i = 1; i <= n; i++) {
        SumB[i] = SumB[i - 1] + B[i];
    }

    // 가능한 모든 경우의 조각 계산
    PizzaA.push_back(0);
    PizzaB.push_back(0);
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j <= m; j++) {
            PizzaA.push_back(SumA[j] - SumA[i]);
            if (i >= 1 && j != m) {
                PizzaA.push_back(SumA[m] - (SumA[j] - SumA[i]));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            PizzaB.push_back(SumB[j] - SumB[i]);
            if (i >= 1 && j != n) {
                PizzaB.push_back(SumB[n] - (SumB[j] - SumB[i]));
            }
        }
    }

    sort(PizzaA.begin(), PizzaA.end());
    sort(PizzaB.begin(), PizzaB.end());

    int cnt = 0;

    for (int i = 0; i <= order; i++) {
        int SizeA = i;
        int SizeB = order - i;

        int idxA = lower_bound(PizzaA.begin(), PizzaA.end(), SizeA) - PizzaA.begin();
        int idxB = lower_bound(PizzaB.begin(), PizzaB.end(), SizeB) - PizzaB.begin();

        int cntA = 0;
        int cntB = 0;

        for (int i = idxA; i < PizzaA.size(); i++) {
            if (PizzaA[i] == SizeA) cntA++;
            else break;
        }
        for (int i = idxB; i < PizzaB.size(); i++) {
            if (PizzaB[i] == SizeB) cntB++;
            else break;
        }

        cnt += (cntA * cntB);
    }

    cout << cnt << "\n";

    return 0;
}