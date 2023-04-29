#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int n, k;
queue<int> q;

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) { int m; cin >> m; q.push(m); }
	while (k--) q.pop(), q.push(0);
	while (!q.empty()) cout << q.front() << ' ', q.pop();
	return 0;
}