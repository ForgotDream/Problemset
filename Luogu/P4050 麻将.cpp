/**
 * @file    P4050 麻将.cpp
 * @author  ForgotDream
 * @brief   枚举
 * @date    2023-02-10
 */
#include <bits/stdc++.h>
#include <cstring>

using namespace std;
using i64 = long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 450;
int n, m;
int card[N];
vector<int> ans;

bool check() {
	static int tmp[N];
	for (int i = 1; i <= n; i++) {
		if (card[i] >= 2) {
			bool flg = true;
			memcpy(tmp, card, sizeof(card));
			tmp[i] -= 2;

			for (int j = 1; j <= n + 2; j++) {
				if (tmp[j] < 0) {
					flg = false;
					break;
				}
				tmp[j] %= 3;
				tmp[j + 1] -= tmp[j], tmp[j + 2] -= tmp[j];
			}

			if (flg) return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1, u; i <= 3 * m + 1; i++) cin >> u, card[u]++;

	for (int i = 1; i <= n; i++) {
		card[i]++;
		if (check()) ans.push_back(i);
		card[i]--;
	}

	if (ans.empty()) cout << "NO" << '\n';
	else {
		sort(ans.begin(), ans.end());
		for (int i : ans) cout << i << ' ';
		cout << '\n';
	}
	return 0;
}