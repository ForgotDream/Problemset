/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-02-19
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e4 + 50, K = 1e4 + 50, M = 1010, INF = 0x3f3f3f3f;
int n, m, k;
int up[N], down[N];
struct Pipe {
	int x, upDis, dwnDis;
} myPipe[K];
int pipeNum[N];
int f[N][M], flg, ans;

bool check(int i, int j) {
	if (!pipeNum[i]) return true;
	auto p = myPipe[pipeNum[i]];
	if (j > p.upDis && j < p.dwnDis) return true;
	else return false;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		cin >> up[i] >> down[i];
	}
	for (int i = 1; i <= k; i++) {
		cin >> myPipe[i].x >> myPipe[i].upDis >> myPipe[i].dwnDis;
		pipeNum[myPipe[i].x] = i;
	}

	memset(f, 0x3f, sizeof(f));
	if (pipeNum[0]) {
		auto p = myPipe[pipeNum[0]];
		for (int i = p.upDis + 1; i < p.dwnDis; i++) {
			f[0][i] = 0;
		}
	} else {
		for (int i = 1; i <= m; i++) {
			f[0][i] = 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		int stY = 1, edY = m;

		for (int j = stY; j <= edY; j++) {
			if (j > up[i - 1]) {
				f[i][j] = min(f[i][j], f[i - 1][j - up[i - 1]] + 1);
				f[i][j] = min(f[i][j], f[i][j - up[i - 1]] + 1);
			}
			if (j == m) {
				for (int k = m - up[i - 1]; k <= m; k++) {
					f[i][m] = min(f[i][m], f[i - 1][k] + 1);
					f[i][m] = min(f[i][m], f[i][k] + 1);
				}
			}
		}

		if (pipeNum[i]) {
			auto p = myPipe[pipeNum[i]];
			for (int j = 0; j <= p.upDis; j++) f[i][j] = INF;
			for (int j = p.dwnDis; j <= m; j++) f[i][j] = INF;
			// cerr << p.dwnDis << ' ' << p.upDis << '\n';
		}

		if (pipeNum[i]) {
			stY = myPipe[pipeNum[i]].upDis + 1;
			edY = myPipe[pipeNum[i]].dwnDis - 1;
		} else {
			stY = 1;
			edY = m;
		}
		// cerr << stY << ' ' << edY << '\n';
		for (int j = edY; j >= stY; j--) {
			// cerr << j << ' ';
			if (j + down[i - 1] <= m) {
				f[i][j] = min(f[i][j], f[i - 1][j + down[i - 1]]);
				// cerr << i << ' ' << j << '\n';
			}
		}
		// cerr << '\n';

		bool allInf = true;
		for (int j = 0; j <= m; j++) {
			if (f[i][j] != INF) {
				allInf = false;
				break;
			}
		}
		if (allInf) {
			flg = i;
			break;
		}
	}

	if (flg) {
		for (int i = 0; i < flg; i++) {
			if (pipeNum[i]) {
				ans++;
			}
		}
		cout << 0 << '\n' << ans << '\n';
	} else {
		ans = INF;
		for (int i = 0; i <= m; i++) {
			ans = min(ans, f[n][i]);
		}
		cout << 1 << '\n' << ans << '\n';
	}

	return 0;
}