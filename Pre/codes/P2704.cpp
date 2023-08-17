#include <iostream>

using namespace std;

int n, m, l;
int map[105], cnt_[1 << 10];
int state[100];
int f[105][1 << 10][1 << 10];

int calc (int x) {
	int res = 0;
	int xx = x;
	for (; xx; xx >>= 1) {
		if (xx & 1) res++;
	}
	return res;
}

int pre () {
	int cnt = 0;
	for (int i = 0; i < (1 << m); i++)
		if (((i & (i << 1)) == 0) && ((i & (i << 2)) == 0) && ((i & (i >> 1)) == 0) && ((i & (i >> 2)) == 0)) state[cnt++] = i, cnt_[i] = calc(i);
	//for (int i = 0; i < cnt; i++) {
	//	cout << state[i] << ' ';
	//}
	//cout << endl;
	return cnt;
}

void solve () {
	int ans = -1;	
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < l; j++)
			for (int k = 0; k < l; k++)
				for (int p = 0; p < l; p++)
					if (((state[j]&state[p]) == 0) && ((state[j]&state[k]) == 0) && ((state[j]&map[i]) == 0))
						f[i][state[j]][state[k]] = max(f[i][state[j]][state[k]], f[i - 1][state[k]][state[p]] + cnt_[state[j]]);
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++)
			ans = max(ans, f[n][state[i]][state[j]]);
	cout << ans << endl;
	return;
}

int main () {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			char ch;
			cin >> ch;
			x = ch == 'P' ? 0 : 1;
			map[i] = (map[i] << 1) + x;
		}
	}
	l = pre();
	solve();
	return 0;
}
