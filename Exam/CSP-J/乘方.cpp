#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

ll a, b;
ll res;

int main() {
	cin >> a >> b;
	res = a;
	if (a == 1) {
		cout << 1 << endl;
		return 0;
	}
	for (int i = 1; i < b; i++) {
		if (res > 1e9) {
			cout << -1 << endl;
			return 0;
		}
		res *= a;
	}
	if (res > 1e9) {
		cout << -1 << endl;
		return 0;
	}
	cout << res << endl;
	return 0;
}