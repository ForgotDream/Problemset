#include <iostream>

using namespace std;

int t, a, c;

int gcd (int m, int n) {
	return m % n == 0 ? n : gcd(n, m % n);
}

int f(int a, int d) {
	int g = gcd(a, d);
	if (g == 1) return d;
	else return d * f(a / g, g);
}

void solve () {
	if (c % a != 0) {
		cout << "NO SOLUTION" << endl;
		return;
	} else {
		cout << f(a, c / a) << endl;
	}
	return;
}

int main () {
	cin >> t;
	while (t--) {
		cin >> a >> c;
		solve();
	}
	return 0;
}
