#include <iostream>

using namespace std;

int t, g, l;

void solve () {
	if (l % g == 0) cout << g << " " << l << endl;
	else cout << -1 << endl;
	return;
}

int main () {
	cin >> t;
	while (t--) {
		cin >> g >> l;
		solve();
	}
	return 0;
}
