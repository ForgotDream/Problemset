#include <iostream>

using namespace std;

int q, n, m;
struct guest {
	int t, h, l;
} l[105];

int main () {
	cin >> q;
	while (q--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			cin >> l[i].t >> l[i].l >> l[i].h;
		}
		int ch = m, cl = m;
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			int dt = l[i].t - l[i - 1].t;
			ch += dt, cl -= dt;
			ch = min(ch, l[i].h), cl = max(cl, l[i].l);
			if (cl > ch) {
				flag = false;
			}
		}
		if (flag) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
