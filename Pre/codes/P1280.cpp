#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int ans = 1;
int n, k, f[(int)1e4 + 50], b[(int)1e4 + 50];
struct work {
	int t, p, e;
} a[(int)1e4 + 50];

bool cmp(const work& a, const work& b) {
	return a.p > b.p;
}

void solve() {
	sort(a + 1, a + k + 1, cmp);
	for (int i = n; i >= 1; i--) {
		if (!b[i]) f[i] = f[i + 1] + 1;
		else
			for (int j = 1; j <= b[i]; j++) {
				f[i] = max(f[i + a[ans].t], f[i]);
				ans++;
			}
	}
	cout << f[1] << endl;
	return;
}

int main() {
	cin >> n >> k;
	for (int i = 1 ; i <= k; i++) cin >> a[i].p >> a[i].t, a[i].e = a[i].p + a[i].t - 1, b[a[i].p]++;
	solve();
	return 0;
}