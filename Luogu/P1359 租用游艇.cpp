#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n;
int link[205][205];

void solve() {
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				link[i][j] = min(link[i][j], link[i][k] + link[k][j]);
	cout << link[1][n] << endl;
	return;
}

int main() {
	memset(link, 0x3f, sizeof link);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		link[i][i] = 0;
		for (int j = i + 1; j <= n; j++)
			cin >> link[i][j];
	}
	solve();
	return 0;
}