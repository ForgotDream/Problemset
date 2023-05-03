# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 3 * 1e5 + 50, Inf = 0x3f3f3f3f; // 131072
template <class T> inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
}
template <typename T> inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
} 
int n, m, root;
int son[N][2], co[N];
i64 dis[N][2];
void dfs(int u)
{
	if(son[u][0]) dfs(son[u][0]);
	if(son[u][1]) dfs(son[u][1]);
	int x = son[u][0], y = son[u][1];
	if(x == 0 && y == 0) return;
	if(co[u] == 1) {
		dis[u][1] = dis[x][1] + dis[y][1];
		//dis[u][0] = min(dis[x][1] + dis[y][0], min(dis[x][0] + dis[y][1] , dis[x][0] + dis[y][0]));
		dis[u][0] = min(dis[x][0], dis[y][0]);
		//if(dis[x][1] >= Inf || dis[y][0] >= Inf) dis[u][0] = 0;
	}
	if(co[u] == 2) {
		dis[u][0] = dis[x][0] + dis[y][0];
		//dis[u][0] = min(dis[x][1] + dis[y][0], min(dis[x][0] + dis[y][1] , dis[x][1] + dis[y][1]));
		dis[u][1] = min(dis[x][1], dis[y][1]);
	}
	if(co[u] == 3) {
		dis[u][0] = min(dis[x][1] + dis[y][1], dis[x][0] + dis[y][0]);
		dis[u][1] = min(dis[x][1] + dis[y][0], dis[x][0] + dis[y][1]);
		
	}
	//cerr <<u <<" " <<dis[u][0] <<" " <<dis[u][1] <<endl;
	return;
}
int main()
{
	freopen("logical.in", "r", stdin);
	freopen("logical.out", "w", stdout);
	Read(n); Read(m);
	for(int i = 1; i <= n; i ++) {
		dis[i][0] = dis[i][1] = Inf;
	}
	for(int i = 1, x, y, z; i <= n; i ++) {
		Read(x); Read(y); Read(z); Read(co[i]);
		son[i][0] = x; son[i][1] = y;
		if(z == 0 && x != 0) root = i;
	}
	
	for(int i = 1, x, y; i <= m; i ++) {
		Read(x); Read(y);
		dis[x][y] = 0;
		y = (y == 1) ? 0 : 1;
		dis[x][y] = 1;
	}
	dfs(root);
	if(dis[root][0] == 0) {
		//cout <<dis[root][1] <<endl;
		print(dis[root][1]);
	} 
	else {
		//cout <<dis[root][0] <<endl;
		print(dis[root][0]);
	}
	return 0;
}
