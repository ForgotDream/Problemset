#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const int M = 1e5 + 50;
int n, m;
priority_queue<int, vector<int>, greater<int> > e[M];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push(v);
		e[v].push(u);
	}
	for (int i = 1; i <= n; i++) {
		cout << e[i].size() << ' ';
		while (!e[i].empty()) {
			int t = e[i].top();
			cout << t << ' ';
			e[i].pop();
		}
		cout << endl;
	}
	return 0;
}