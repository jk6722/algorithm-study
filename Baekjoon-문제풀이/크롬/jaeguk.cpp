#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;
using ll = long long;

const int MAX_N = 100 + 5;
const int MAX_M = 1000 + 5;
const int MAX_P = 500 + 5;
vector<tiii> tabs;
int N, M, K;
int DP[MAX_M][MAX_P];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    cin >> N >> M >> K;
    int cpu, mem, priority;
    for(int i = 0; i < N; i++) {
        cin >> cpu >> mem >> priority;
        tabs.push_back({cpu, mem, priority});
    }

    memset(DP, -1, sizeof(DP));
    DP[0][0] = 0;

    for(int n = 0; n < N; n++) {
        auto [cpu, mem, priority] = tabs[n];

        for(int i = M; i >= 0; i--) {
            for(int j = 5 * N - priority; j >= 0; j--) {
                if(DP[i][j] == -1) continue;

                int next_i = min((i + cpu), M); // 어짜피 M 이상의 CPU를 확보하면 M으로 고정해도 됨
                int next_j = j + priority;
                DP[next_i][next_j] = max(DP[next_i][next_j], DP[i][j] + mem);
            }
        }
    }

    int ans = -1;
    for(int i = 0; i <= 5 * N; i++)
        if(DP[M][i] >= K) {
            ans = i;
            break;
        }

    cout << ans << "\n";

	return 0;
}