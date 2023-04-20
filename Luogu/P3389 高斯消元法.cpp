#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPS = 1e-8;
const int N = 105;
double a[N][N];
int n;

bool gaussJordan() {
	for (int i = 1; i <= n; i++) {
		int pivot = i;
		for (int j = i + 1; j <= n; j++) 
			if (fabs(a[j][i]) > fabs(a[pivot][i])) pivot = j;
		for (int j = 1; j <= n + 1; j++) swap(a[i][j], a[pivot][j]);
		if (fabs(a[i][i]) < EPS) return false;
		for (int j = n + 1; j >= 1; j--) a[i][j] /= a[i][i];
		for (int j = 1; j <= n; j++)
			if (j != i) {
				double tmp = a[j][i] / a[i][i];
				for (int k = 1; k <= n + 1; k++) a[j][k] -= a[i][k] * tmp;
			}
	}
	return true;
}

void solve() {
	if (!gaussJordan()) return (void)(cout << "No Solution" << endl);
	else for (int i = 1; i <= n; i++) cout << fixed << setprecision(2) << a[i][n + 1] << endl;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n + 1; j++)
			cin >> a[i][j];
	solve();
	return 0;
}