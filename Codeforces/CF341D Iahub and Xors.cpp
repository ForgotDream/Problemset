#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 1050, INF = 0x3f3f3f3f;
int n, m;
ll t[2][2][N][N], num;
int opt, a, b, c, d;

inline int lowbit(int x) {
	return x & -x;
}

inline void update(int x, int y, int num) {
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= n; j += lowbit(j))
			t[x & 1][y & 1][i][j] ^= num;
	return;
}

inline ll sum(int x, int y) {
	ll res = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			res ^= t[x & 1][y & 1][i][j];
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	while (m--) {
		cin >> opt >> a >> b >> c >> d;
		if (opt == 1) cout << (sum(a - 1, b - 1) ^ sum(a - 1, d) ^ sum(c, b - 1) ^ sum(c, d)) << endl;
		else {
			cin >> num;
			update(a, b, num), update(a, d + 1, num);
			update(c + 1, b, num), update(c + 1, d + 1, num);
		}
	}
	return 0;
}