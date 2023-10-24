// TLE on test #1 1.13s
// KM 的板子都是紫的，这个题绿？

#include <iostream>
#include <cstdio>

using namespace std;

const int N = 25;
int n;
int a[N][N], b[N][N], f[N][1 << 20];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) 
			cin >> a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> b[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < (1 << n); j++)
			for (int k = 1; k <= n; k++)
				if (j >> (k - 1) & 1) f[i][j] = max(f[i][j], f[i - 1][j - (1 << (k - 1))] + a[i][k] * b[k][i]);
	cout << f[n][(1 << n) - 1] << endl;
	return 0;
}