#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;
long long f[2050][2050];
int add[500], del[500];
int n, m;
string str;

void solve() {
	for (int len = 2; len <= m; len++) {
		for (int l = 0; l + len - 1 < m; l++) {
			int r = l + len - 1;
			f[l][r] = INF;
			if (str[l] == str[r]) f[l][r] = f[l + 1][r - 1];
			else f[l][r] = min(f[l][r - 1] + min(add[str[r]], del[str[r]]), f[l + 1][r] + min(add[str[l]], del[str[l]]));
		}
	}
	cout << f[0][m - 1] << endl;
	return;
}

int main() {
	cin >> n >> m;
	cin >> str;
	for (int i = 1; i <= n; i++) {
		char c;
		int x, y;
		cin >> c >> x >> y;
		add[(int)c] = x, del[(int)c] = y;
	}
	solve();
	return 0;
}