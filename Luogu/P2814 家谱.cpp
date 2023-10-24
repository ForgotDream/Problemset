#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_map>

const int M = 5e4 + 50;
using namespace std;
unordered_map<string, int> mp;
int cnt;
char c;
string str, lst;
int fa[M];
string Hash[M];

void init() {
	for (int i = 1; i < M; i++) fa[i] = i;
	return;
}

int find(int u) {
	return fa[u] == u ? u : fa[u] = find(fa[u]);
}

void combine(int x, int y) {
	int fa_x = find(x), fa_y = find(y);
	if (fa_x != fa_y) fa[fa_y] = fa_x;
	return;
}

int main() {
	init();
	while (cin >> c && c != '$') {
		cin >> str;
		if (c == '#') {
			lst = str;
			if (!mp.count(str)) mp[str] = ++cnt;
			Hash[cnt] = str;
		} else if (c == '+') {
			if (!mp.count(str)) mp[str] = ++cnt;
			auto it_ch = mp.find(str), it_fa = mp.find(lst);
			combine((*it_fa).second, (*it_ch).second);
		} else {
			cout << str << ' ';
			int u = find(mp[str]);
			cout << Hash[u] << endl;
		}
	}
	return 0;
}