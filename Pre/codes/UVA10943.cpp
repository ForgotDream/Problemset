#include <iostream>

using namespace std;

const int M = 1e6;
int n, k;
int f[105][105];

void init () {
	for (int i = 0; i <= 100; i++)
		for (int j = 1; j <= 100; j++)
			if (j == 1) f[i][j] = 1;
			else for (int m = 0; m <= i; m++) f[i][j] = (f[i][j] + f[m][j - 1]) % M;
	return;
}

int main () {
	init();
	while (cin >> n >> k) {
		if (n == 0 && k == 0) break;
		//solve();
		cout << f[n][k] << endl;
	}
	return 0;
}
