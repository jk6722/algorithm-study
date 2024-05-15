#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int idx;
int C, N, Q;
vector<int> idxs;

unordered_set<string> teams;

struct Trie {
	bool finish;
	Trie* next[26];
	
	Trie() : finish(false) {
		memset(next, 0, sizeof(next));
	}

	~Trie() {
		for(int i = 0; i < 26; i++) {
			if(next[i])
				delete next[i];
		}
	}

	void insert(const char* key) {
		if(*key == '\0') finish = true;
		else {
			int curr = *key - 'a'; // 현재 문자의 인덱스
			if(next[curr] == NULL)
				next[curr] = new Trie();
			
			next[curr]->insert(key + 1);
		}
	}

	Trie* find(const char* key) {
		//모든 가능한 지점 저장
		if(finish) idxs.push_back(idx);

		if(*key == '\0') return this;
		int curr = *key - 'a';
		idx++;
		if(next[curr] == NULL) return NULL;
		return next[curr]->find(key + 1); //다음 문자 탐색
	}
};

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Trie* colors = new Trie();

	cin >> C >> N;

	char temp[2001];
	for(int i = 0; i < C; i++) {
		//색상 입력
		cin >> temp;
		colors->insert(temp);
	}

	string team;
	for(int i = 0; i < N; i++) {
		//팀 입력
		cin >> team;
		teams.insert(team);
	}

	cin >> Q;

	for(int i = 0; i < Q; i++) {
		//쿼리 요청
		idx = 0;
		idxs.clear();

		cin >> temp;
		Trie* ret = colors->find(temp);

		if(idxs.size() == 0) {
			//색상이 없음
			cout << "No\n";
			continue;
		}

		bool chk = false;
		for(auto it : idxs) {
			string str(temp + it);
			if(teams.count(str)){
				cout << "Yes\n";
				chk = true;
				break;
			}
		}
		if(!chk) cout << "No\n";
	}

	delete colors;

	return 0;
}