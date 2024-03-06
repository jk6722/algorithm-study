#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
int N;

int press = 0;

struct Trie {
    bool finish;
    bool isRoot;
    int cnt;
    Trie* child[26];
    
    Trie() {
        finish = false;
        isRoot = false;
        cnt = 0;
        memset(child, 0, sizeof(child));
    }

    ~Trie() {
        for(int i = 0; i < 26; i++) {
            if(child[i]) delete child[i];
        }
    }

    void insert(const char* key) {
        if(*key == '\0') {
            cnt++;
            finish = true;
        }
        else {
            int cur = *key - 'a';
            if(child[cur] == NULL){
                cnt++;
                child[cur] = new Trie();
            }
            child[cur]->insert(key + 1);
        }
    }

    bool find(const char* key) {
        if(*key == '\0') {
            if(finish) return true;
            return false;
        }

        if(cnt != 1 || isRoot) {
            press++;
        }

        int cur = *key - 'a';

        if(child[cur] == NULL) return false;
        return child[cur]->find(key + 1);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    vector<string> words;

    while(true) {

        Trie *root = new Trie();
        root->isRoot = true;
        words.clear();

        cin >> N;

        if(cin.eof()) break;
        
        for(int i = 0; i < N; i++) {
            cin >> str;
            words.push_back(str);
            root->insert(str.c_str());
        }

        int total_press = 0;
        for(auto word : words) {
            press = 0;
            root->find(word.c_str());
            total_press += press;
        }

        cout << fixed;
        cout.precision(2);

        double average = (double)total_press / (double)N;
        cout << average << "\n";

        delete(root);
    }

    return 0;
}