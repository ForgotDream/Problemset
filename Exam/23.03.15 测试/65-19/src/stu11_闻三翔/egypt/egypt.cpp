# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 110, Inf = 0x3f3f3f3f;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) {x = -x; putchar('-');}
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, m, a[N][N][N];
int _next[5][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int up[4][2] = {{0, 0}, {0, -1}, {-1, 0}, {-1, -1}};
int vis[N][N][N], ans = Inf;
int have[N][N][N];
long long T;
struct node {
	int a1, b1, c1, a2, b2, c2, t;
} path[N];
void dfs(int step, int x, int y, int cost)
{
	T ++;
	if(T >= 110000000) {
		print(ans + a[n][1][1]);
		exit(0);
	}
	if(step == n && x == 1 && y == 1) {
		ans = min(ans, cost);
		return ;
	}
	if(cost >= vis[step][x][y] || cost >= ans) return;
	vis[step][x][y] = cost;
	if(have[step][x][y]) {
		int id = have[step][x][y];
		dfs(path[id].a2, path[id].b2, path[id].c2, cost + path[id].t + a[step][x][y]);
	}
	for(int i = 0; i <= 3; i ++) {
		int dx = x + up[i][0], dy = y + up[i][1];
		if(dx < 1 || dx > n - step || dy < 1 || dy > n - step) continue;
		dfs(step + 1, dx, dy, cost + a[step][x][y]);
	}
	for(int i = 0; i <= 3; i ++) {
		int dx = x + _next[i][0], dy = y + _next[i][1];
		if(dx < 1 || dx > n - step + 1 || dy < 1 || dy > n - step + 1) continue;
		dfs(step, dx, dy, cost + a[step][x][y]);
	}
}
int main()
{
	freopen("egypt.in", "r", stdin);
	freopen("egypt.out", "w", stdout);
	Read(n); Read(m);
	for(int i = n; i >= 1; i --) {
		for(int j = 1; j <= i; j ++) {
			for(int k = 1; k <= i; k ++) {
				Read(a[n - i + 1][j][k]);
			}
		}
	} 
	for(int i = 1; i <= m; i ++) {
		Read(path[i].a1); Read(path[i].b1); Read(path[i].c1);
		Read(path[i].a2); Read(path[i].b2); Read(path[i].c2);
		Read(path[i].t);
		have[path[i].a1][path[i].b1][path[i].c1] = i;
	}
	memset(vis, 0x3f, sizeof(vis));
	dfs(1, 1, 1, 0);
	print(ans + a[n][1][1]);
	return 0;
}
