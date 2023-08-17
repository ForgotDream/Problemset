#include <iostream>

using namespace std;

const int M = 1e9;
int m, n, f[13][4096], F[13], mat[13][13];
bool state[4096];

void pre () {
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			F[i] = (F[i] << 1) + mat[i][j];
	int tot = 1 << n;
	for (int i = 0; i < tot; i++)
		state[i] = ((i & (i << 1)) == 0) && ((i & (i >> 1)) == 0);
	f[0][0] = 1;
	return;
}

void solve () {
	int tot = 1 << n;
	pre();
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < tot; j++)
			if (state[j] && ((j & F[i]) == j))
				for (int k = 0; k < tot; k++)
					if ((k & j) == 0)
						f[i][j] = (f[i][j] + f[i - 1][k]) % M;
	int ans = 0;
	for (int i = 0; i < tot; i++)
		ans += f[m][i], ans %= M;
	cout << ans << endl;
	return;
}

int main() {
	cin >> m >> n;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> mat[i][j];
	solve();
	return 0;
}
