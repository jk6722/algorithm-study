#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int A, B;
int N, M;
const int MAX_N = 100 + 5;
int robot[MAX_N][MAX_N]; // 로봇의 현황
pair<int, int> robot_pos[MAX_N];

char dir[MAX_N]; // 로봇의 방향

void turn(int robot_num, char cmd) {
    char now = dir[robot_num];
    if (cmd == 'L') {
        // 왼쪽으로 회전
        if (now == 'N') dir[robot_num] = 'W';
        else if (now == 'E') dir[robot_num] = 'N';
        else if (now == 'S') dir[robot_num] = 'E';
        else if (now == 'W') dir[robot_num] = 'S';
    }
    else if (cmd == 'R') {
        // 오른쪽으로 회전
        if (now == 'N') dir[robot_num] = 'E';
        else if (now == 'E') dir[robot_num] = 'S';
        else if (now == 'S') dir[robot_num] = 'W';
        else if (now == 'W') dir[robot_num] = 'N';
    }
}

void move(int robot_num) {
    pair<int, int> now = robot_pos[robot_num];
    char now_dir = dir[robot_num];
    robot[now.first][now.second] = 0;
    pair<int, int> next = now;

    // 방향에 따라 이동
    if (now_dir == 'W') next = { next.first - 1, next.second };
    else if (now_dir == 'S') next = { next.first, next.second - 1 };
    else if (now_dir == 'E') next = { next.first + 1, next.second };
    else if (now_dir == 'N') next = { next.first, next.second + 1 };

    if (next.first < 1 || next.first > A || next.second < 1 || next.second > B) {
        // 이동하려는 칸이 벽인 경우
        cout << "Robot " << robot_num << " crashes into the wall" << "\n";
        exit(0);
    }
    else if (robot[next.first][next.second]) {
        // 이동하려는 칸에 다른 로봇이 있는 경우
        cout << "Robot " << robot_num << " crashes into robot " << robot[next.first][next.second] << "\n";
        exit(0);
    }
    else {
        // 로봇 옮기기
        robot_pos[robot_num] = next;
        robot[next.first][next.second] = robot_num;
    }
}

void do_command(char cmd, int robot_num, int times) {
    switch (cmd)
    {
        case 'L':
        case 'R':
            for (int i = 0; i < times; i++) {
                turn(robot_num, cmd);
            }
            break;
        case 'F':
            for (int i = 0; i < times; i++) {
                move(robot_num);
            }
            break;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> A >> B;
    cin >> N >> M;

    int x, y;
    char direc;

    for (int i = 1; i <= N; i++) {
        cin >> x >> y >> direc;
        robot[x][y] = i;
        robot_pos[i] = { x, y };
        dir[i] = direc;
    }

    int robot_num, times;
    char cmd;

    for (int i = 0; i < M; i++) {
        cin >> robot_num >> cmd >> times;
        do_command(cmd, robot_num, times);
    }
    cout << "OK\n";
    return 0;
}