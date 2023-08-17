# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
# include <vector>
using namespace std;
const int N = 100, Inf = 0x3f3f3f3f;
const double eps = 1e-5;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar())<'0' || ch > '9') if(ch == '-') base = -1;
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
} 
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
} 
int n, vis[N][N], used[N], sum, m;
struct node {
	int x, y;
	bool p[7][7];
}a[N];
bool _change(int x, int y, int id, int k)
{
	if(x + a[id].x - 1 > m || y + a[id].y - 1 > m) return false;
	for(int i = x; i <= x + a[id].x - 1; i ++) {
		for(int j = y; j <= y + a[id].y - 1; j ++) {
			if(vis[i][j] && a[id].p[i - x + 1][j - y + 1] == 1) return false;
			if(a[id].p[i - x + 1][j - y + 1] == 1) vis[i][j] = id;
		}
	}
	return true;
}
void dfs(int x, int y, int step)
{
	if(y >= m) x ++, y = 1;
	else y ++;
	if(step >= n + 1) {
		for(int i = 1; i <= m; i ++) {
			for(int j = 1; j <= m; j ++) {
				print(vis[i][j]);
			}
			putchar('\n');
		}
		exit(0);
	}
	int tmp[N][N];
	memcpy(tmp, vis, sizeof(vis));
	if(vis[x][y]) dfs(x, y, step);
	else {
		for(int i = 1; i <= n; i ++) {
			if(used[i]) continue;
			if(_change(x, y, i, i) == 1) {
				used[i] = 1;
				dfs(x, y, step + 1);
				used[i] = 0;
			}
			memcpy(vis, tmp, sizeof(vis));
		}
	}	
}
int main()
{
	freopen("puzzling.in", "r", stdin);
	freopen("puzzling.out", "w", stdout);
	cin >>n;
	for(int i = 1, x, y; i <= n; i ++) {
		cin >>x >>y;
		a[i].x = x; a[i].y = y;
		char ch[15];
		for(int j = 1; j <= x; j ++) {
			cin >>(ch + 1);
			for(int k = 1; k <= y; k ++) {
				a[i].p[j][k] = ch[k] - '0';
				if(ch[k] == '1') sum ++;
			}
		}
	}
	m = sqrt(sum);
	dfs(1, 0, 1);
	print(-1);
	return 0;
}
