#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

int n;
long long c;
map<int, int> mp;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int m, d = 0;
		cin >> m;
		auto it = mp.lower_bound(m);
		if (it != mp.end()) d = max(d, it->second + 1);
		if (it != mp.begin()) d = max(d, (--it)->second + 1);
		mp[m] = d, c += d;
		cout << c << endl;
	}
	return 0;
}