#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits.h>
#include <cstring>
using namespace std;

const int MAX_N = 16 + 1;
const int IMPOSSIBLE = 15000000 + 5;
int W[MAX_N][MAX_N];
int N, check;
int DP[MAX_N][65536];

int dfs(int now, int visited) {
	//방문 체크
	visited = visited | (1 << now);

	if (visited == check) {
		//모든 노드 방문 완료
		if (W[now][0] == 0) return IMPOSSIBLE; //돌아가는 길이 없다면
		return W[now][0];
	}

	int &ret = DP[now][visited];
	if (ret != -1) {
		return ret;
	}

	ret = IMPOSSIBLE;
	//방문하지 않은 모든 도시 순회
	for (int i = 0; i < N; i++) {
		if (((1 << i) & visited) == 0 && W[now][i] > 0) {
			//방문한 적이 없으면
			ret = min(ret, dfs(i, visited) +  W[now][i]);
		}
	}
	return ret;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	memset(DP, -1, sizeof(DP));

	cin >> N;

	check = (1 << N) - 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> W[i][j];
		}
	}

	cout << dfs(0, 0) << "\n";

	return 0;
}
