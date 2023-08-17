#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int M = 19650827;
int n, a[1050];
int lef[1050][1050], rig[1050][1050];

void solve() {
	for (int i = 1; i <= n; i++) lef[i][i] = 1;
	for (int len = 1; len <= n; len++) {
		for (int l = 1; l + len - 1 <= n; l++) {
			int r = l + len - 1;
			if (a[l] < a[l + 1]) lef[l][r] += lef[l + 1][r];
			if (a[l] < a[r]) lef[l][r] += rig[l + 1][r];
			if (a[r] > a[r - 1]) rig[l][r] += rig[l][r - 1];
			if (a[r] > a[l]) rig[l][r] += lef[l][r - 1];
			lef[l][r] %= M, rig[l][r] %= M;
		} 
	}
	cout << (lef[1][n] + rig[1][n]) % M << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	solve();
	return 0;
}