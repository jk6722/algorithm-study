#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;

vector<pll> town;
int N;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  ll X, A;
  ll sum = 0;
  for (int i = 0; i < N; i++) {
    cin >> X >> A;
    town.push_back({X, A});
    sum += A;
  }

  sort(town.begin(), town.end());

  ll now_sum = 0;
  for (auto it : town) {
    now_sum += it.second;
    if (now_sum >= (sum + 1) / 2) {
      cout << it.first << "\n";
      break;
    }
  }

  return 0;
}
