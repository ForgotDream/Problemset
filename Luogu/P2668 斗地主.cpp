/**
 * @file    P2668 斗地主.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-02-09
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 20;
int card[N];
int T, n, ans;

void dfs(int cur) {
	if (cur >= ans) return;
	
	int tmp = 0;
	for (int i = 3; i <= 14; i++) 
		if (!card[i]) tmp = 0;
		else {
			tmp++;
			if (tmp >= 5) {
				for (int j = i; j >= i - tmp + 1; j--) card[j]--;
				dfs(cur + 1);
				for (int j = i; j >= i - tmp + 1; j--) card[j]++;
			}
		}

	tmp = 0;
	for (int i = 3; i <= 14; i++) {
		if (card[i] <= 1) tmp = 0;
		else {
			tmp++;
			if (tmp >= 3) {
				for (int j = i; j >= i - tmp + 1; j--) card[j] -= 2;
				dfs(cur + 1);
				for (int j = i; j >= i - tmp + 1; j--) card[j] += 2;
			}
		}
	}

	tmp = 0;
	for (int i = 3; i <= 14; i++) {
		if (card[i] <= 2) tmp = 0;
		else {
			tmp++;
			if (tmp >= 2) {
				for (int j = i; j >= i - tmp + 1; j--) card[j] -= 3;
				dfs(cur + 1);
				for (int j = i; j >= i - tmp + 1; j--) card[j] += 3;
			}
		}
	}

	tmp = 0;
	for (int i = 2; i <= 14; i++) {
		if (card[i] <= 2) continue;
		if (card[i] <= 3) {
			card[i] -= 3;
			for (int j = 2; j <= 15; j++) {
				if (!card[j] || j == i) continue;
				card[j]--, dfs(cur + 1), card[j]++;
			}
			for (int j = 2; j <= 14; j++) {
				if (card[j] <= 1 || j == i) continue;
				card[j] -= 2, dfs(cur + 1), card[j] += 2;
			}
			card[i] += 3;
		}
		else {
			card[i] -= 3;
			for (int j = 2; j <= 15; j++) {
				if (!card[j] || j == i) continue;
				card[j]--, dfs(cur + 1), card[j]++;
			}
			for (int j = 2; j <= 14; j++) {
				if (card[j] <= 1 || j == i) continue;
				card[j] -= 2, dfs(cur + 1), card[j] += 2;
			}
			card[i] += 3;

			card[i] -= 4;
			for (int j = 2; j <= 15; j++) {
				if (!card[j] || i == j) continue;
				card[j]--;
				for (int k = 2; k <= 15; k++) {
					if (!card[k] || j == k) continue;
					card[k]--, dfs(cur + 1), card[k]++;
				}
				card[j]++;
			}
			for (int j = 2; j <= 14; j++) {
				if (card[j] <= 1 || i == j) continue;
				card[j] -= 2;
				for (int k = 2; k <= 14; k++) {
					if (card[k] <= 1 || j == k) continue;
					card[k] -= 2, dfs(cur + 1), card[k] += 2;
				}
				card[j] += 2;
			}
			card[i] += 4;
		}
	}

	for (int i = 2; i <= 15; i++) if (card[i]) cur++;

	ans = min(ans, cur);
	return;
}

inline void init() {
	memset(card, 0, sizeof(card));
	ans = 0x7fffffff;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> T >> n;
	while (T--) {
		init();

		for (int i = 1, x, y; i <= n; i++) {
			cin >> x >> y;
			if (x == 0) card[15]++;
			else if (x == 1) card[14]++;
			else card[x]++;
		}

		dfs(0);
		cout << ans << '\n';
	}

	return 0;
}