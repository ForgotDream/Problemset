#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <set>

using namespace std;

char mat[10][10];
int ans1 = 0, ans2 = 0;
int cnt;

bool check(double x) {
	return x >= 1 && x <= 9 && (x - (int)x == 0);
}

map<double, set<pair<double, double>> > mp; 

void solve() {
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			for (int l = 1; l <= 9; l++)
				for (int k = 1; k <= 9; k++)
					if (mat[i][j] == '#' && mat[l][k] == '#' && (i != l || j != k)) {
						double lx, ly, rx, ry;
						lx = ((i + l) + (k - j)) / 2.0;
						ly = ((j + k) + (i - l)) / 2.0;
						rx = ((i + l) - (k - j)) / 2.0;
						ry = ((j + k) - (i - l)) / 2.0;
						if (check(lx) && check(ly) && check(rx) && check(ry) && mat[(int)lx][(int)ly] == '#' && mat[(int)rx][(int)ry] == '#') ans2++;
						if (check(lx) && check(ly) && check(rx) && check(ry) && mat[(int)lx][(int)ly] == '#' && mat[(int)rx][(int)ry] == '#') {
							// cout << i << ' ' << j << ' ' << l << ' ' << k << "  ";
							// cout << lx << ' ' << ly << ' ' << rx << ' ' << ry << endl;
							// cout << (check(lx) && check(ly) && check(rx) && check(ry) && mat[(int)lx][(int)ly] == '#' && mat[(int)rx][(int)ry] == '#') << endl;
							// cout << endl;
							double midx = abs(i + l), midy = abs(j + k);
							double length = hypot(i - l, j - k);
							mp[length].insert(make_pair(midx, midy));
						}
					}
	for (auto it : mp) {
		// cout << ans1 << endl;
		ans1 += it.second.size();
		// cout << it.first << endl;
		// for (auto sit : it.second) cout << sit.first << ' ' << sit.second << endl;
		// cout << ans1 << endl << endl;
	}
	cout << ans1 << endl;
	return;
}

int main() {
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++) 
			cin >> mat[i][j];
	solve();
	return 0;
}