#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long ull;

int n;
ull num;
int tmp[64];

ull g(ull n) {
	return n ^ (n >> 1);
}

void solve() {
	ull ans = g(num);
	int cnt = 0;
	while (ans) {
		// cout << (ans & 1);
		tmp[++cnt] = ans & 1;
		ans >>= 1;
	}
	for (int i = n; i > 0; i--) {
		cout << tmp[i];
	}
	return;
}

int main() {
	cin >> n >> num;
	// cout << num << endl;
	solve();
	return 0;
}