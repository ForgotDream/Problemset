#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 45;
const int S = (1<<20) + 7;

int n, k;

int a[N], pa;
int b[N], pb;
int c[S], tot;
long long ans;

void init()
{
	cin >> n >> k;
	for(int i = 0; i < n; ++ i) cin >> a[i];

	pa = n / 2;
	pb = n - pa;
	for(int i = pa; i < n; ++ i) b[i - pa] = a[i];	
}

void dfs(int x, int y)
{
	if(y > k) return;

	if(x == pa)
	{
		c[tot++] = y;
		return;
	}

	dfs(x+1, y), dfs(x+1, y+a[x]);
}

void dfs2(int x, int y)
{
	if(y > k) return;

	if(x == pb)
	{
		ans += upper_bound(c, c+tot, k-y) - c;
		return;
	}

	dfs2(x+1, y), dfs2(x+1, y+b[x]);
}

void prep()
{
	tot = 0;
	dfs(0, 0);
	sort(c, c+tot);
}

void solve()
{
	ans = 0;
	dfs2(0, 0);
	cout << ans << endl;
}

int main()
{
	freopen("ticket.in", "r", stdin);
	freopen("ticket.out", "w", stdout);

	init();
	prep();
	solve();

	return 0;
}
