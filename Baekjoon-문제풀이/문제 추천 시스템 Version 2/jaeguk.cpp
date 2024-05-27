#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int N, M;

const int MAX_N = 100 + 5;
set<pii> problems_group[MAX_N]; //알고리즘 분류별 문제
set<int> problems_level[MAX_N]; //난이도별 문제
unordered_map<int, pii> problems_info; //문제별 분류와 난이도

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	int P, L, G;
	for(int i = 0; i < N; i++) {
		cin >> P >> L >> G;
		problems_group[G].insert({L, P});
		problems_level[L].insert(P);
		problems_info[P] = {G, L};
	}

	cin >> M;
	string cmd;
	int x;
	for(int m = 0; m < M; m++) {
		// 명령문 실행
		cin >> cmd;
		if(cmd == "recommend") {
			cin >> G >> x;
			auto it = x == 1 ? --problems_group[G].end() : problems_group[G].begin();
			cout << (*it).second << "\n";
		}
		else if(cmd == "recommend2") {
			cin >> x;
			if(x == 1) {
				// 전체에서 가장 어려운 문제
				for(int i = 100; i >= 1; i--) {
					if(!problems_level[i].empty()) {
						auto it = --problems_level[i].end();
						cout << (*it) << "\n";
						break;
					}
				}
			}
			else if(x == -1) {
				// 전체에서 가장 쉬운 문제
				for(int i = 1; i <= 100; i++) {
					if(!problems_level[i].empty()) {
						auto it = problems_level[i].begin();
						cout << (*it) << "\n";
						break;
					}
				}
			}
		}
		else if(cmd == "recommend3") {
			cin >> x >> L;
			if(x == 1) {
				bool chk = false;
				for(int i = L; i <= 100; i++) {
					if(!problems_level[i].empty()) {
						auto it = problems_level[i].begin();
						cout << (*it) << "\n";
						chk = true;
						break;
					}
				}

				if(!chk) cout << "-1\n";
			}
			else if(x == -1) {
				bool chk = false;
				for(int i = L - 1; i >= 1; i--) {
					if(!problems_level[i].empty()) {
						auto it = --problems_level[i].end();
						cout << (*it) << "\n";
						chk = true;
						break;
					}
				}

				if(!chk) cout << "-1\n";
			}

		}
		else if(cmd == "add") {
			cin >> P >> L >> G;
			problems_group[G].insert({L, P});
			problems_level[L].insert(P);
			problems_info[P] = {G, L};
		}
		else if(cmd == "solved") {
			cin >> P;
			auto [group, level] = problems_info[P];
			problems_group[group].erase({level, P});
			problems_level[level].erase(P);
		}
	}

	return 0;
}