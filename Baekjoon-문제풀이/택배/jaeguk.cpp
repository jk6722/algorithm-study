#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

const int MAX_N = 2000 + 5;
vector<tiii> box;
int truck[MAX_N];

int N, C, M;

bool comp(tiii& a, tiii& b) {
  auto [a1, a2, a3] = a;
  auto [b1, b2, b3] = b;

  if (a2 == b2) return a1 < b1;
  return a2 < b2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> C;
  cin >> M;

  int u, v, w;
  for (int i = 0; i < M; i++) {
    cin >> u >> v >> w;
    box.push_back({u, v, w});
  }

  sort(box.begin(), box.end(), comp);

  int ans = 0;
  for (int i = 0; i < box.size(); i++) {
    auto [u, v, w] = box[i];
    int max_cnt = 0;
    for (int j = u; j < v; j++) {
      max_cnt = max(max_cnt, truck[j]);
    }

    int load = min(w, C - max_cnt);

    for (int j = u; j < v; j++) {
      truck[j] += load;
    }

    ans += load;
  }
  cout << ans << "\n";

  return 0;
}
