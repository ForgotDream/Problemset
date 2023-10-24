#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 5050;
int n, m;
int ans;
int graph[N][N], f[N];
bool used[N];
int x, y, z;

void solve() {
	int cur = 1;
	memset(f, 0x7f, sizeof f);
	f[1] = 0;
	for (int i = 1; i <= n; i++) {
		int minn = 0x7f7f7f7f;
		for (int j = 1; j <= n; j++) 
			if (!used[j] && f[j] < minn) minn = f[j], cur = j;
		ans = max(minn, ans), used[cur] = true;
		for (int j = 1; j <= n; j++) 
			if (!used[j] && graph[j][cur] < f[j]) f[j] = graph[j][cur];
	}
	for (int i = 1; i <= n; i++)
		if (!used[i]) {
			cout << -1 << endl;
			return;
		}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> m;
	memset(graph, 0x7f, sizeof graph);
	for (int i = 1; i <= n; i++) graph[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> z;
		graph[x][y] = min(z, graph[x][y]), graph[y][x] = min(z, graph[y][x]);
	}
	solve();
	return 0;
}