#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, less<int> > big;
priority_queue<int, vector<int>, greater<int> > small;

const int M = 2e5 + 50;
int n, m;
int a[M], u[M];

void maintain(int k) {
	if (small.size() < k) 
		while (small.size() < k) small.push(big.top()), big.pop();
	if (small.size() > k) 
		while (small.size() > k) big.push(small.top()), small.pop();
	return;
}

void add(int u, int k) {
	// maintain(k);
	if (small.empty() || u > small.top()) small.push(u);
	else big.push(u);
	maintain(k);
	return;
}

void get(int k) {
	maintain(k);
	cout << -1 * small.top() << endl;
	maintain(k);
}

void solve() {
	int kth = 1, cnt = 1;
	for (int i = 1; i <= m; i++) {
		int query = u[i];
		// cout << '#' << query << ' ' << cnt << endl;
		for (int j = cnt; j <= query; j++) {
			add(-1 * a[j], kth);
			// cout << a[j] << ' ';
		}
		//cout << endl;
		get(kth);
		kth++;
		cnt = query + 1;
	}
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) cin >> u[i];
	solve();
	return 0;
}