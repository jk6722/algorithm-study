#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000 + 5;
int RGB[MAX_N][3];
int DP[3];
int N;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 3; j++)
			cin >> RGB[i][j];

	for (int i = 1; i < N; i++) {
		RGB[i][0] += min(RGB[i - 1][1], RGB[i - 1][2]);
		RGB[i][1] += min(RGB[i - 1][0], RGB[i - 1][2]);
		RGB[i][2] += min(RGB[i - 1][0], RGB[i - 1][1]);
	}

	cout << min(RGB[N - 1][0], min(RGB[N - 1][1], RGB[N - 1][2])) << "\n";
	
	return 0;
}