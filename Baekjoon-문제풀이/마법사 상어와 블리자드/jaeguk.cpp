#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using pii = pair<int,int>;

const int MAX_N = 49 + 5;
int board[MAX_N][MAX_N];
//블리자드용
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
//상어 이동용
int move_dy[] = {0, 1, 0, -1};
int move_dx[] = {-1, 0, 1, 0};

//상어의 위치
pii shark;
int N, M;

//최종 출력
int exploded_marble = 0;

vector<vector<pii>> groups;

void blizard(int, int);
void fill_board(vector<int>&);
void rearrange();
void find_groups();
int explode();
void remake();

void blizard(int d, int s) {
    for(int i = 1; i <= s; i++) {
        pii next = {shark.first + dy[d] * i, shark.second + dx[d] * i};
        board[next.first][next.second] = 0;
    }
}

void fill_board(vector<int>& marbles) {
    //다시 돌면서 구슬 배치
    pii now = shark;
    int len = 1;
    int cnt = 0;
    int dir = 0;
    bool toggle = false;
    int marble_idx = 0;
    while(true) {
        pii next = {now.first + move_dy[dir], now.second + move_dx[dir]};
        if(next.second < 0) break;
        board[next.first][next.second] = marble_idx >= marbles.size() ? 0 : marbles[marble_idx++];
        now = next;
        cnt++;

        if(cnt == len){
            dir = (dir + 1) % 4;
            cnt = 0;
            
            if(toggle) len++;
            toggle = !toggle;
        }
    }
}

void rearrange() {
    // 구슬 재배열
    pii now = shark;
    int len = 1;
    int cnt = 0; //현재 방향으로 이동한 횟수
    int dir = 0;
    bool toggle = false;
    vector<int> marbles;

    // 빈칸이 아닌 구슬 탐색
    while(true) {
        pii next = {now.first + move_dy[dir], now.second + move_dx[dir]};
        if(next.second < 0) break;

        if(board[next.first][next.second]) marbles.push_back(board[next.first][next.second]);
        now = next;
        cnt++;

        if(cnt == len){
            dir = (dir + 1) % 4;
            cnt = 0;

            if(toggle) len++;
            toggle = !toggle;
        }
    }

    fill_board(marbles);
}

void find_groups() {
    groups.clear();

    pii now = shark;
    int len = 1;
    int cnt = 0;
    int dir = 0;
    bool toggle = false;

    vector<pii> group;
    int prev = board[shark.first][shark.second - 1]; 

    while(true) {
        pii next = {now.first + move_dy[dir], now.second + move_dx[dir]};
        if(next.second < 0) break;

        now = next;
        cnt++;

        if(prev == board[now.first][now.second]) {
            group.push_back(now);
        }
        else {
            //다르면
            groups.push_back(group);

            group.clear();
            prev = board[now.first][now.second];
            group.push_back(now);
        }

        if(cnt == len){
            dir = (dir + 1) % 4;
            cnt = 0;

            if(toggle) len++;
            toggle = !toggle;
        }
    }

    if(!group.empty()) {
        groups.push_back(group);
    }
}

int explode() {
    // 구슬 폭발
    int exploded = 0;
    find_groups();
    
    for(auto group : groups) {
        if(group.size() >= 4) {
            //폭발
            int marbel_num = board[group[0].first][group[0].second];
            exploded_marble += marbel_num * group.size();
            
            if(marbel_num) exploded += group.size();

            for(auto it : group) {
                board[it.first][it.second] = 0;
            }
        }
    }
    rearrange();
    
    return exploded;
}

void remake() {
    find_groups();
    vector<int> marbles;

    for(auto group : groups) {
        if(!board[group[0].first][group[0].second]) continue;
        // 구슬 A
        marbles.push_back(group.size());
        // 구슬 B
        marbles.push_back(board[group[0].first][group[0].second]);
    }

    fill_board(marbles);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    shark = {(N + 1) / 2 - 1, (N + 1) / 2 - 1};
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    int di, si;
    for(int i = 0; i < M; i++) {
        cin >> di >> si;
        blizard(di - 1, si);
        rearrange();
        while(explode());
        remake();
    }

    cout << exploded_marble << "\n";

    return 0;
}