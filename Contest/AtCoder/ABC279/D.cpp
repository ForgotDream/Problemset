#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>

using namespace std;
using ll = long long;

long double a, b, EPS = 1e-7;

long double calc(long double u) {
	return (long double)b * u + (long double)a / sqrt((long double)u + 1);
}

void solve() {
	long double l = 1, r = a;
	while (r > l) {
		long double mid1 = l + (r - l) / 3, mid2 = r + (l - r + 2) / 3;
		long double fl = calc(mid1), fr = calc(mid2);
		// cout << mid1 << ' ' << mid2 << endl;
		if (fl >= fr + EPS)
			l = mid1 + 1;
		else
			r = mid2 - 1;
	}
	// cout << l << endl;
	// cout << l << ' ' << calc(l) << endl;
	cout << fixed << setprecision(10) << min(min(calc(l), calc(r)), calc(0)) << endl;
	// cout << fixed << setprecision(10) << calc(29240177372 + 1) << endl;
	return;
}

int main() {
	cin >> a >> b;
	solve();
	return 0;
}
// 8772053214538.5976562500
// 8772053214538.5986328125
