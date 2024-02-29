#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100000 + 5;
vector<pair<int,int>> Edge;
bool isCut[MAX_N]; //분할 여부
vector<int> cuts; //분할할 선의 인덱스
int parent[MAX_N];
int setSize[MAX_N]; //집합의 크기
int N, M ,Q;

void init() {
    for(int i = 1; i <= N; i++) {
        parent[i] = i;
        setSize[i] = 1;
    }
}

int Find(int x) {
    if(parent[x] == x) return x;
    else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    int parent_x = Find(x);
    int parent_y = Find(y);

    //parent_y의 부모를 parent_x로 변경
    parent[parent_y] = parent_x;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;

    init();

    int u, v;
    for(int i = 0; i< M; i++) {
        cin >> u >> v;
        Edge.push_back({u,v});
    }

    int cut = 0;
    for(int i = 0; i < Q; i++) {
        cin >> cut;
        cuts.push_back(cut - 1);
        isCut[cut - 1] = true;
    }

    for(int i = 0; i < Edge.size(); i++) {
        if(!isCut[i]) {
            // 분할될 선이 아니라면 미리 Union
            pair<int,int> now = Edge[i];
            int parent_x = Find(now.first);
            int parent_y = Find(now.second);

            if(parent_x != parent_y) {
                setSize[parent_x] += setSize[parent_y];
                Union(parent_x, parent_y);
            }
        }
    }

    // 마지막으로 잘린 간선부터 역으로 합치면서 확인
    reverse(cuts.begin(), cuts.end());

    ll cost = 0;

    for(auto it : cuts) {
        pair<int,int> now =Edge[it];

        int parent_x = Find(now.first);
        int parent_y = Find(now.second);

        if(parent_x != parent_y) {
            // 분할비용 발생
            cost += ((ll)setSize[parent_x] * (ll)setSize[parent_y]);
            setSize[parent_x] += setSize[parent_y];
            Union(parent_x, parent_y);
        }
    }
    
    cout << cost << "\n";

    return 0;
}