/**
 * @file    P2593 超级麻将.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-02-10
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 105;
int n, card[N];

bool check() {
	static bool f[N][N][N][2];
	memset(f, 0, sizeof(f));
	f[0][0][0][0] = true;
	for (int i = 1; i <= 100; i++) 
		for (int j = 0; j <= card[i - 1]; j++)
			for (int k = 0; k <= card[i]; k++) {
				if (k > 1) f[i][j][k][1] |= f[i][j][k - 2][0];
				if (k > 2) f[i][j][k][1] |= f[i][j][k - 3][1], f[i][j][k][0] |= f[i][j][k - 3][0];
				if (k > 3) f[i][j][k][1] |= f[i][j][k - 4][1], f[i][j][k][0] |= f[i][j][k - 4][0];
				if (j >= k && card[i - 2] >= k) f[i][j][k][1] |= f[i - 1][card[i - 2] - k][j - k][1], 
												f[i][j][k][0] |= f[i - 1][card[i - 2] - k][j - k][0];
			}
	return f[100][card[99]][card[100]][1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	while (n--) {
		for (int i = 1; i <= 100; i++) cin >> card[i];
		if (check()) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}

	return 0;
}