#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using pii = pair<int,int>;

const int MAX_N = 20 + 5;
int board[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int dy[] = {0, 1, 0, -1};
int dx[] = {-1, 0, 1, 0};
int N, M;

vector<pii> to_delete;
vector<pii> group;
vector<pii> rainbows;

int max_score;
int max_rainbow;
int score;
int rainbow_cnt;
int now_color;

bool is_ok(pii pos) {
    if(pos.first < 0 || pos.first >= N || pos.second < 0 || pos.second >= N
        || visited[pos.first][pos.second] || board[pos.first][pos.second] == -1) return false;
    return true;
}

void find_group(pii now) {
    visited[now.first][now.second] = true;
    group.push_back(now);
    if(board[now.first][now.second] == 0){
        rainbow_cnt++;
        rainbows.push_back(now);
    }
    score++;

    for(int i = 0; i < 4; i++) {
        pii next = {now.first + dy[i], now.second + dx[i]};
        if(is_ok(next) && (board[next.first][next.second] == 0 || board[next.first][next.second] == now_color))
            find_group(next);
    }
}

void delete_blocks() {
    for(auto it : to_delete) {
        board[it.first][it.second] = -2;
    }
}

void rotate() {
    int after_rotate[MAX_N][MAX_N];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            after_rotate[N - 1 - j][i] = board[i][j];
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            board[i][j] = after_rotate[i][j];
        }
    }
}

void gravity() {
    for(int j = 0; j < N; j++) {
        pii to_drop = {N - 1, j};
        for(int i = N - 1; i >= 0; i--) {
            if(board[i][j] == -1) {
                //검은 블록
                to_drop = {i - 1,j};
                continue;
            }
            if(board[i][j] == -2) continue; //빈 블록
            if(to_drop == make_pair(i,j)) {
                //제자리면
                to_drop = {i - 1, j};
                continue;
            }

            board[to_drop.first][to_drop.second] = board[i][j];
            board[i][j] = -2;
            to_drop = {to_drop.first - 1, to_drop.second};
        }
    }
}

void restore_rainbow() {
    for(auto it : rainbows) {
        visited[it.first][it.second] = false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    int total_score = 0;

    while(true) {
        max_score = 0;
        max_rainbow = 0;
        to_delete.clear();
        memset(visited, false, sizeof(visited));

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(board[i][j] == 0 || board[i][j] == -1 || board[i][j] == -2) continue;
                group.clear();
                score = 0;
                rainbow_cnt = 0;
                restore_rainbow();
                rainbows.clear();

                now_color = board[i][j];
                find_group({i,j});

                if(group.size() < 2) continue;

                bool flag = false;

                if(max_score < score) {
                    flag = true;
                }
                else if(max_score == score) {
                    if(max_rainbow <= rainbow_cnt) {
                        flag = true;
                    }
                }

                if(flag) {
                    //갱신
                    to_delete = group;
                    max_score = score;
                    max_rainbow = rainbow_cnt;
                }
            }
        }

        if(to_delete.empty()) break;

        total_score += (max_score * max_score);

        delete_blocks();
        gravity();
        rotate();
        gravity();
    }

    cout << total_score << "\n";

    return 0;
}