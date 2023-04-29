#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int M = 2e5 + 50;
unordered_map<int, int> mp;
unordered_set<int> st[2 * M];
int n, q;
int cnt, Hash[2 * M];
int t, a, b;

int main() {
	cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		cin >> t >> a >> b;
		if (!mp.count(a)) mp[a] = ++cnt, Hash[cnt] = a; 
		if (!mp.count(b)) mp[b] = ++cnt, Hash[cnt] = b;
		if (t == 1) {
			st[mp[a]].insert(mp[b]);
		} else if (t == 2) {
			st[mp[a]].erase(mp[b]);
		} else {
			if (st[mp[a]].count(mp[b]) && st[mp[b]].count(mp[a])) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	}
	return 0;
}