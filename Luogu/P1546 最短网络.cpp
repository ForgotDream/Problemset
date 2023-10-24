#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 5050;
int n, m;
long long ans, all;
int graph[N][N], f[N];
bool used[N];
int x, y, z;

void solve() {
	for (int i = 1; i <= n; i++) {
		ans = 0;
		int cur = i;
		memset(f, 0x7f, sizeof f);
		memset(used, 0, sizeof used);
		f[i] = 0;
		for (int i = 1; i <= n; i++) {
			int minn = 0x7f7f7f7f;
			for (int j = 1; j <= n; j++)
				if (!used[j] && f[j] < minn) minn = f[j], cur = j;
			ans += minn, used[cur] = true;
			for (int j = 1; j <= n; j++)
				if (!used[j] && graph[j][cur] < f[j]) f[j] = graph[j][cur];
		}
	}
	cout << all - ans << endl;
	return;
}

int main() {
	cin >> n >> m;
	memset(graph, 0x7f, sizeof graph);
	for (int i = 1; i <= n; i++) graph[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> z;
		all += z;
		graph[x][y] = min(z, graph[x][y]), graph[y][x] = min(z, graph[y][x]);
	}
	solve();
	return 0;
}