#include <iostream>
#include <vector>
using namespace std;
using pii = pair<int,int>;

const int MAX_N  = 10000 + 5;
int N;
int board[15][15];
int score = 0;

void print_board();

bool is_ok(pii pos) {
    if(pos.first > 9 || pos.second > 9 || board[pos.first][pos.second]) return false;
    return true;
}

int check_light_blue() {
    //연한 파란색 보드에 걸친 블럭 수
    int cnt = 0;
    for(int j = 4; j <= 5; j++) {
        for(int i = 0; i < 4; i++) {
            if(board[i][j]) {
                cnt++;
                break;
            }
        }
    }
    return cnt;
}

int check_light_green() {
    //연한 초록색 보드에 걸친 블럭 수
    int cnt = 0;
    for(int i = 4; i <= 5; i++) {
        for(int j = 0; j < 4; j++) {
            if(board[i][j]) {
                cnt++;
                break;
            }
        }
    }

    return cnt;
}

bool check_blue(int st_line) {
    for(int i = 0; i < 4; i++) {
        if(!board[i][st_line]) return false;
    }
    return true;
}

bool check_green(int st_line) {
    for(int j = 0; j < 4; j++) {
        if(!board[st_line][j]) return false;
    }
    return true;
}

void push_blue(int block, int st_line) {
    //st_line부터 block만큼 오른쪽으로 밀기

    for(int j = st_line; j >= 4; j--) {
        for(int i = 0; i < 4; i++) {
            board[i][j + block] = board[i][j];
        }
    }

    for(int j = 4; j < 4 + block; j++) {
        for(int i = 0; i < 4; i++) {
            board[i][j] = 0;
        }
    }
}

void push_green(int block, int st_line) {
    //st_line부터 block만큼 오른쪽으로 밀기

    for(int i = st_line; i >= 4; i--) {
        for(int j = 0; j < 4; j++) {
            board[i + block][j] = board[i][j];
        }
    }

    for(int i = 4; i < 4 + block; i++) {
        for(int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
}

void insert(int t, pii st) {
    if(t == 1) {
        //1X1
        pii blue = st;
        while(true) {
            pii next = {blue.first, blue.second + 1};
            if(!is_ok(next)) break;
            blue = next;
        }

        board[blue.first][blue.second] = 1;

        if(check_blue(blue.second)) {
            score++;
            push_blue(1, blue.second - 1);
        }

        pii green = st;
        while(true) {
            pii next = {green.first + 1, green.second};
            if(!is_ok(next)) break;
            green = next;
        }

        board[green.first][green.second] = 1;
        if(check_green(green.first)) {
            score++;
            push_green(1, green.first - 1);
        }
    }
    else {
        //2X1, 1X2
        pair<pii,pii> blocks;
        if(t == 2) blocks = {st, {st.first, st.second + 1}};
        else if(t == 3) blocks = {st, {st.first + 1, st.second}};

        pair<pii,pii> blue = blocks;
        while(true) {
            pair<pii,pii> next = {{blue.first.first, blue.first.second + 1}, {blue.second.first, blue.second.second + 1}};
            if(!is_ok(next.first) || !is_ok(next.second)) break;
            blue = next;
        }

        board[blue.first.first][blue.first.second] = 1;
        board[blue.second.first][blue.second.second] = 1;

        if(check_blue(blue.first.second)) {
            score++;
            push_blue(1, blue.first.second - 1);
        }
        if(check_blue(blue.second.second)) {
            score++;
            push_blue(1, blue.second.second - 1);
        }

        pair<pii,pii> green = blocks;
        while(true) {
            pair<pii,pii> next = {{green.first.first + 1, green.first.second}, {green.second.first + 1, green.second.second}};
            if(!is_ok(next.first) || !is_ok(next.second)) break;
            green = next;
        }

        board[green.first.first][green.first.second] = 1;
        board[green.second.first][green.second.second] = 1;

        if(check_green(green.first.first)) {
            score++;
            push_green(1, green.first.first - 1);
        }
        if(check_green(green.second.first)) {
            score++;
            push_green(1, green.second.first - 1);
        }
    }

    int cnt = check_light_blue();
    if(cnt > 0) push_blue(cnt, 9 - cnt);

    cnt = check_light_green();
    if(cnt > 0) push_green(cnt, 9 - cnt);
}

int count_board() {
    int cnt = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cnt += board[i][6 + j];
            cnt += board[6 + i][j];
        }
    }
    return cnt;
}

void print_board() {
    for(int i = 0; i < 10; i++) {
        int max_j = i < 4 ? 10 : 4;
        for(int j = 0; j < max_j; j++) {
            cout << board[i][j] << ' ';
        }
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    
    int t, y, x;
    for(int i = 0; i < N; i++) {
        cin >> t >> y >> x;
        insert(t, {y,x});
    }

    cout << score << "\n";
    cout << count_board() << "\n";

    return 0;
}