# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
using namespace std;
const int N = 550, Inf = 0x3f3f3f3f;
int n, m, k1, k2, Mod;
int px[3550], py[3550], ans = Inf;
bool vis[N][N];
int _next[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
void dfs(int x, int y, int id, int maxn)
{
	if(vis[x + 1][y] && vis[x - 1][y] && !vis[x][y + 1] && !vis[x][y - 1]) return;
	if(vis[x][y + 1] && vis[x][y - 1] && !vis[x + 1][y] && !vis[x - 1][y]) return;
	int res = 0;
	if(id <= n*m/2) px[id % Mod] = x, py[id % Mod] = y;
	else {
		int tmp = id % Mod;
		res = k1 * abs(px[tmp] - x) + k2 * abs(py[tmp] - y);
	}
	res = max(res, maxn);
	if(res >= ans) return;
	if(id == n * m) {
		ans = min(ans, res);
		return;
	}
	for(int i = 0; i <= 3; i ++) {
		int dx = x + _next[i][0], dy = y + _next[i][1];
		if(dx < 1 || dx > n || dy < 1 || dy > m || vis[dx][dy]) continue; 
		vis[dx][dy] = 1;
		dfs(dx, dy, id + 1, res);
		vis[dx][dy] = 0;
	}
}
int main()
{
	cin >>n >>m >>k1 >>k2; Mod = n * m / 2;
	vis[1][1] = 1;
	for(int i = 0; i <= m + 1; i ++) { vis[0][i] = 1; vis[n + 1][i] = 1;}
    for(int i = 0; i <= n + 1; i ++) { vis[i][0] = 1; vis[i][m + 1] = 1;}
	dfs(1, 1, 1, 0);
	cout <<ans;
	return 0;
}
