#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 2050, INF = 0x3f3f3f3f;
int n, m;
int t1[N][N], t2[N][N], t3[N][N], t4[N][N]; 
int a, b, c, d, delta;
char opt;

inline int lowbit(int x) {
	return x & -x;
}

inline void update(int x, int y, int num) {
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= m; j += lowbit(j)) 
			t1[i][j] += num, t2[i][j] += x * num, t3[i][j] += y * num, t4[i][j] += x * y * num;
	return;
}

inline int sum(int x, int y) {
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] - (x + 1) * t3[i][j] + t4[i][j];
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> opt >> n >> m;
	while (cin >> opt) {
		cin >> a >> b >> c >> d;
		if (opt == 'L') {
			cin >> delta;
			update(a, b, delta), update(c + 1, d + 1, delta);
			update(a, d + 1, -1 * delta), update(c + 1, b, -1 * delta);
		} else cout << sum(c, d) + sum(a - 1, b - 1) - sum(a - 1, d) - sum(c, b - 1) << endl;
	}
	return 0;
}