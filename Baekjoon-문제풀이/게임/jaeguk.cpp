#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <tuple>
using namespace std;
typedef long long ll;

const int MAX_N = 50 + 5;
string board[MAX_N];
bool visited[MAX_N][MAX_N];
int memory[MAX_N][MAX_N];
int N, M, ans;

int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };

bool flag;

bool isOk(pair<int, int> pos) {
	if (pos.first < 1 || pos.first > N || pos.second < 0 || pos.second >= M ||
		board[pos.first][pos.second] == 'H') return false;
	return true;
}

void dfs(pair<int,int> now, int depth) {
	//이전보다 적은 움직임으로 현재 지점을 방문했다면, 더이상의 움직임은 불필요한 연산
	if (flag || memory[now.first][now.second] >= depth) return;

	//현재 방문한 지점을 방문할 때까지의 이동 횟수를 기록
	memory[now.first][now.second] = depth;
	visited[now.first][now.second] = true;
	int X = board[now.first][now.second] - '0';

	for (int i = 0; i < 4; i++) {
		pair<int, int> next = { now.first + dy[i] * X, now.second + dx[i] * X };
		if (isOk(next)) {
			if (board[now.first][now.second] == board[next.first][next.second]) {
				//다음에 방문할 곳의 X가 현재의 X와 같다면, 무한히 이동 가능
				flag = true;
				return;
			}
			else if(!visited[next.first][next.second]) dfs(next, depth + 1);
			else {
				//만약 이미 방문했던 곳이라면 사이클이 존재한다는 것이므로 무한히 이동 가능
				flag = true;
				return;
			}
		}
		else {
			//더이상 이동이 불가능한 경우 탐색 종료
			ans = max(ans, depth);
		}
	}
	visited[now.first][now.second] = false;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> board[i];
	}

	dfs({ 1, 0 }, 1);
	ans = flag ? -1 : ans;
	cout << ans << "\n";
	return 0;
}