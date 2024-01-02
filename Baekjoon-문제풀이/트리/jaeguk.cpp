#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int T;
int n;
const int MAX_N = 1000 + 5;
int preorder[MAX_N];
int inorder[MAX_N];

void postorder(int st, int ed, int root_idx) {
    for (int i = st; i < ed; i++) {
        if (inorder[i] == preorder[root_idx]) {
            // inorder에서 root를 찾았다면
            postorder(st, i, root_idx + 1);
            postorder(i + 1, ed, root_idx + i + 1 - st);
            cout << preorder[root_idx] << " ";
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> preorder[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> inorder[i];
        }
        postorder(0, n, 0);
        cout << "\n";
    }

    return 0;
}