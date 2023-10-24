#include <iostream>
#include <cstdio>

using namespace std;

int n, root;
int l[50], r[50];

void solve(int cur) {
	cout << char(cur + 'a');
	if (l[cur] != '*' - 'a') solve(l[cur]);
	if (r[cur] != '*' - 'a') solve(r[cur]);
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char u, lu, ru;
		cin >> u >> lu >> ru;
		if (i == 1) root = u - 'a';
		l[u - 'a'] = lu - 'a';
		r[u - 'a'] = ru - 'a';
	}
	solve(root);
	return 0;
}