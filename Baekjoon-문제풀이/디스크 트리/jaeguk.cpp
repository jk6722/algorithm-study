#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

struct tree {
	string dirname;
	int depth; //띄어쓰기를 위해 필요
	map<string, tree*> childs;
};

vector<string> inputs;
int N;

// 부모 디렉토리를 먼저 출력하기 위해서는 inorder로 돌아야 함
void inorder(tree* now) {
	if(now->dirname != "") {
		for(int i = 0; i < now->depth; i++)
			cout << " ";
		cout << now->dirname << "\n";
	}
	for(auto [key, ptr] : now->childs) {
		inorder(ptr);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	tree* root = new tree();
	root->dirname = "";
	root->depth = -1;

	cin >> N;
	string cmd;
	for(int i = 0; i < N; i++) {
		cin >> cmd;
		inputs.push_back(cmd);
	}

	// 사전순 출력을 위해 정렬
	sort(inputs.begin(), inputs.end());

	for(auto input : inputs) {
		string token;
		stringstream ss(input);
		vector<string> tokens;

		while(getline(ss, token, '\\')) {
			tokens.push_back(token);
		}
		
		tree* now = root;
		for(auto path : tokens) {
			if(now->childs[path] != NULL) {
				now = now->childs[path];
			}
			else {
				now->childs[path] = new tree();
				now->childs[path]->dirname = path;
				now->childs[path]->depth = now->depth + 1;
				now = now->childs[path];
			}
		}
	}

	inorder(root);
	
	return 0;
}