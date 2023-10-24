/**
 * @file    T312883 棋盘放置指南车.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-02-09
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1;
int T, n, ans;
char mat[10][10];
int atk[10][10], have[10][10];

void dfs(int curx = 1, int cury = 1, int cur = 0) {
	if (cur > ans) ans = cur;
	if (curx > n) return;
	if (mat[curx][cury] == 'x' || atk[curx][cury]) return (void) (dfs(curx + (cury == n), (cury % n) + 1, cur));

	//--------------------------------------------------------------------------------

	bool flg = true;

	for (int i = cury + 1; i <= n; i++) {
		if (mat[curx][i] == 'x') break;
		else {
			if (have[curx][i]) {
				flg = false;
				// break;
			}
			atk[curx][i]++;
		}
	}

	for (int i = cury - 1; i >= 1; i--) {
		if (mat[curx][i] == 'x') break;
		else {
			if (have[curx][i]) {
				flg = false;
				// break;
			}
			atk[curx][i]++;
		}
	}

	if (flg) have[curx][cury] = true, dfs(curx + (cury == n), cury % n + 1, cur + 1), have[curx][cury] = false;

	for (int i = cury + 1; i <= n; i++) {
		if (mat[curx][i] == 'x') break;
		else atk[curx][i]--;
	}

	for (int i = cury - 1; i >= 1; i--) {
		if (mat[curx][i] == 'x') break;
		else atk[curx][i]--;
	}

	//--------------------------------------------------------------------------------

	flg = true;

	for (int i = curx + 1; i <= n; i++) {
		if (mat[i][cury] == 'x') break;
		else {
			if (have[i][cury]) {
				flg = false;
				// break;
			}
			atk[i][cury]++;
		}
	}

	for (int i = curx - 1; i >= 1; i--) {
		if (mat[i][cury] == 'x') break;
		else {
			if (have[i][cury]) {
				flg = false;
				// break;
			}
			atk[i][cury]++;
		}
	}

	if (flg) have[curx][cury] = true, dfs(curx + (cury == n), cury % n + 1, cur + 1), have[curx][cury] = false;

	for (int i = curx + 1; i <= n; i++) {
		if (mat[i][cury] == 'x') break;
		else atk[i][cury]--;
	}

	for (int i = curx - 1; i >= 1; i--) {
		if (mat[i][cury] == 'x') break;
		else atk[i][cury]--;
	}

	//--------------------------------------------------------------------------------

	dfs(curx + (cury == n), cury % n + 1, cur);

	return;
}

inline void init(int n) {
	memset(have, 0, sizeof(have));
	memset(atk, 0, sizeof(atk));
	memset(mat, 0, sizeof(mat));
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> T;
	for (int i = 1; i <= T; i++) {
		init(n);
		cin >> n, ans = 0;
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= n; j++) 
				cin >> mat[i][j];

		dfs();
		cout << ans << '\n';
	}

	return 0;
}