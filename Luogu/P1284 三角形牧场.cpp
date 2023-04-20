#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int N = 45, M = 805;
int n;
int a[N], sum;
double ans = -1;
bool f[M][M];

bool check(int x, int y, int z) {
	return (x + y > z) && (x + z > y) && (y + z > x);
}

double calc(double x, double y, double z) {
	double p = 1.0 * (x + y + z) / 2;
	return sqrt(p * (p - x) * (p - y) * (p - z));
}

void solve() {
	f[0][0] = true;
	for (int i = 1; i <= n; i++) 
		for (int j = sum / 2; j >= 0; j--) 
			for (int k = sum / 2; k >= 0; k--) {
				if (j - a[i] >= 0 && f[j - a[i]][k]) f[j][k] = true;
				if (k - a[i] >= 0 && f[j][k - a[i]]) f[j][k] = true;
			}
	for (int i = sum / 2; i > 0; i--)
		for (int j = sum / 2; j > 0; j--) {
			if (!f[i][j]) continue;
			if (check(i, j, sum - i - j)) ans = max(ans, calc(i, j, sum - i - j));
		}
	if (ans == -1) return (void)(cout << -1 << endl);
	return (void)(cout << (long long)(ans * 100) << endl);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
	solve();
	return 0;
}