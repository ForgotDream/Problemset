#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int M = 1e5 + 50;
int n, m;
int dir[M], cur;
string name[M];

void solve() {
	cur = 1;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		if (dir[cur]) {
			if (!x) {
				cur = (cur + y + 1) % n + 1;
			} else {
				cur = ((cur - y + 1) % n + n) % n + 1;
			}
		} else {
			if (x) {
				cur = (cur + y + 1) % n + 1;
			} else {
				cur = ((cur - y + 1) % n + n) % n + 1;
			}
		}
	}
	cout << name[cur] << endl;
	return;
}

int main() {
	freopen("toy1.in", "r", stdin);
	freopen("toy.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> dir[i] >> name[i];
	}
	
	solve();
	return 0;
}
