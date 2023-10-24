#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int h, w;
char tmp;
vector<string> v1((int)4e5 + 50);
vector<string> v2((int)4e5 + 50);

void solve() {
	sort(v1.begin() + 1, v1.begin() + w + 1);
	sort(v2.begin() + 1, v2.begin() + w + 1);
	for (int i = 1; i <= w; i++) {
		if (v1[i] != v2[i]) {
			cout << "No" << endl;
			return;
		}
	}
	cout << "Yes" << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> h >> w;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++) {
			cin >> tmp;
			v1[j].push_back(tmp);
		}
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++) {
			cin >> tmp;
			v2[j].push_back(tmp);
		}
	solve();
	return 0;
}