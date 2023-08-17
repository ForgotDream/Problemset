# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
using namespace std;
const int N = 4000, D = 1e6, Inf = 0x3f3f3f3f;
typedef long long i64;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar())<'0' || ch >'9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar())>='0' && ch <='9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x /10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
i64 H, g[1005][1005], n, ans = Inf;
bool vis[N];
struct node {
	i64 x, y;
}a[N];
void dfs(i64 pos, i64 sum, i64 h)
{
	if(sum >= ans) return;
	if(h + 1000 >= H) {
		ans = min(ans, sum);
		return;
	}
	for(int i = 1; i <= n; i ++) {
		if(vis[i] || i == pos) continue;
		if(g[pos][i]) {
			vis[i] = 1;
			dfs(i, sum + 1, a[i].y);
			vis[i] = 0;
		}	
 	}
}
int main()
{
	freopen("wall.in", "r", stdin);
	freopen("wall.out", "w", stdout);
	Read(H); Read(n);
	for(int i = 1; i <= n; i ++) {
		Read(a[i].x); Read(a[i].y);
	}
	a[0].x = 0; a[0].y = 0;
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j < i; j ++) {
			i64 dis = (a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y);
			if(dis <= D) g[i][j] = 1, g[j][i] = 1;
		}
	dfs(0, 0, 0);
	print(ans);
	return 0;
}
