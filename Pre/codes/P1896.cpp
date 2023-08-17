#include <iostream>

using namespace std;

typedef long long ll;

int n, k, l;
ll f[10][1 << 9][100];
ll state[1 << 9];
ll sum[1 << 9];

ll calc (int x) {
	ll res = 0;
	for (; x; x >>= 1)
		if (x & 1) res++;
	return res;
}

ll pre () {
	ll cnt = 0;
	for (int i = 0; i < (1 << n); i++)
		if ((i & (i >> 1)) == 0 && (i & (i << 1)) == 0) state[cnt++] = i, sum[i] = calc(i);
	return cnt;
}

void solve () {
	//f[0][1][0] = 1;
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < l; j++)
			for (int p = 0; p <= k; p++)
				if (p >= sum[state[j]])
					for (int t = 0; t < l; t++)
						if (((state[j] & state[t]) == 0) && ((state[t] & (state[j] >> 1)) == 0) && ((state[t] & (state[j] << 1)) == 0))
							f[i][state[j]][p] += f[i - 1][state[t]][p - sum[state[j]]];
	long long res = 0;
	for (int i = 0; i < l; i++)
		res += f[n][state[i]][k];
	cout << res << endl;
	return;
}

int main () {
	cin >> n >> k;
	l = pre();
	solve();
	return 0;
}