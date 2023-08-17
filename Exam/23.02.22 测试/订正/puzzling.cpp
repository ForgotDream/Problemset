#include <iostream>
#include <cmath>

using namespace std;

const int N = 30;
struct Component {
	int x, y;
	bool a[N][N];
} comp[N];
int n, a[N][N], m;
int all;

bool put(int id, int sx, int sy, int cnt) {
	int x = comp[id].x, y = comp[id].y;
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			if (comp[id].a[i][j]) {
				int dx = sx + i - 1, dy = sy + j - 1;
				if (a[dx][dy] != 0 && a[dx][dy] != cnt) {
					return false;
				} else if (dx > m || dy > m) {
					return false;
				}
			}
		}
	}
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			if (comp[id].a[i][j]) {
				int dx = sx + i - 1, dy = sy + j - 1;
				a[dx][dy] = cnt;
			}
		}
	}
	return true;
}

void clear(int cnt) {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == cnt) a[i][j] = 0;
		}
	}
	return;
}

void dfs(int state, int cnt) {
	if (state == (1 << n) - 1) {
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				cout << a[i][j];
			}
			cout << '\n';
		}
		exit(0);
	}
	for (int i = 1; i <= n; i++) {
		if (state & (1 << (i - 1))) {
			continue;
		}
		for (int j = 1; j <= m; j++) {
			for (int k = 1; k <= m; k++) { 
				if (put(i, j, k, cnt + 1)) {
					dfs(state | 1 << (i - 1), cnt + 1);
					clear(cnt + 1);
				}
			}
		}
	}
	return;
}

int main() {
	freopen("puzzling.in", "r", stdin);
	freopen("puzzling.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> comp[i].x >> comp[i].y;
		for (int j = 1; j <= comp[i].x; j++) {
			for (int k = 1; k <= comp[i].y; k++) {
				char c;
				cin >> c;
				comp[i].a[j][k] = (c == '1');
				all += (c == '1');
			}
		}
	}
	
	m = sqrt(all);
	if (m * m != all) {
		cout << -1 << '\n';
		return 0;
	}
	
	dfs(0, 0);
	
	cout << -1 << '\n';
	
	return 0;
}
