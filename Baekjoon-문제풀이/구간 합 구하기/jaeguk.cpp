#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;

const int MAX_N = 1000000 + 5;
int N, M, K, start;
ll tree[MAX_N * 3]; //세그먼트 트리

void update(int i, ll target) {
	//i번째 노드를 target으로 변경
	int nodeIdx = start + i;
	ll gap = target - tree[nodeIdx];

	//루트노드까지 업데이트
	while (nodeIdx > 0) {
		tree[nodeIdx] += gap;
		nodeIdx /= 2; //부모 노드로 이동
	}
}

ll get(int left, int right) {
	//left ~ right 사이의 구간합 구하기
	ll sum = 0;

	//tree 배열에서의 인덱스로 변환
	left = left + start;
	right = right + start;

	/*
	트리에서 왼쪽 노드는 무조건 짝수번 인덱스, 오른쪽은 홀수번 인덱스
	구간을 서서히 좁히면서 구간 사이의 합을 구한다

	left가 오른쪽 자식에 위치해있으면 (홀수이면), 오른쪽으로 이동하게 되면 이동 후의 부모에게 내가 포함되지 않음
	=> 미리 sum에 더해두고 이동한다.

	같은 원리로 right가 왼쪽 자식에 위치해있으면 (짝수이면), 왼쪽으로 이동하게 되면 이동 후의 부모에게 내가 포함되지 않음
	=> 미리 sum에 더해두고 이동한다.
	*/

	while (left <= right) {
		if (left % 2 == 1) {
			//left가 홀수이면
			//더하고 한칸 오른쪽으로
			sum += tree[left];
			left++;
		}
		if (right % 2 == 0) {
			//right가 짝수이면
			//더하고 한칸 왼쪽으로
			sum += tree[right];
			right--;
		}
		left /= 2;
		right /= 2;
	}

	return sum;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> K;

	//트리의 크기를 확인하기 위한 초기화
	int treeSize = 1;

	//노드가 전부 들어갈 수 있는 크기를 찾는다.
	while (treeSize < N) {
		treeSize *= 2;
	}

	memset(tree, 0, treeSize * 2);
	start = treeSize - 1; //트리 인덱스를 찾기위한 값

	for (int i = 1; i <= N; i++) {
		//리프노드 입력
		cin >> tree[start + i];
	}

	for (int i = start; i >= 0; i--) {
		//중간 노드에는 자식 노드의 합을 저장
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}
	
	int a;
	ll b, c;
	for (int i = 1; i <= M + K; i++) {
		//변경 또는 구간합
		cin >> a >> b >> c;
		switch (a) {
		case 1:
			//변경
			update(b, c);
			break;
		case 2:
			//구간합
			cout << get(b, c) << "\n";
			break;
		}
	}

	return 0;
}