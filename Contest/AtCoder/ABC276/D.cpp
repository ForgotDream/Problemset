#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, cnt, tmp;
int a[1050], _gcd;
bool flag = true;

int gcd(int m, int n) {
	return n ? gcd(n, m % n) : m;
}

void solve() {
	sort(a + 1, a + n + 1);
	while (a[1] % 3 == 0 && a[1] != _gcd && (a[1] / 3) % _gcd == 0) a[1] /= 3, cnt++;
	while (a[1] % 2 == 0 && a[1] != _gcd && (a[1] / 2) % _gcd == 0) a[1] /= 2, cnt++;
	for (int i = 2; i <= n; i++) {
		bool eq = false;
		if (a[i] % a[i - 1] != 0) {
			flag = false;
			break;
		}
		while (a[i] % 3 == 0 && a[i] != _gcd && (a[i] / 3) % _gcd == 0) {
			if (a[i] == a[i - 1]) {
				eq = true;
				break;
			}
			a[i] /= 3, cnt++;
		}
		// cout << a[i] << ' ';
		while (a[i] % 2 == 0 && a[i] != _gcd && (a[i] / 2) % _gcd == 0) {
			if (a[i] == a[i - 1]) {
				eq = true;
				break;
			}
			a[i] /= 2, cnt++;
		}
		// cout << a[i] << ' ' << a[i - 1] << endl;
		if (a[i] != a[i - 1]) {
			flag = false;
			break;
		}
	}
	if (!flag) cout << -1 << endl;
	else cout << cnt << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], _gcd = gcd(a[i], _gcd);
	solve();
	return 0;
}