#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;
const int M = 2e6 * 2 + 7;

int n, q;
int cx, cy;
int ax[N], ay[N], bx[N], by[N];
int tax[M];

void init()
{
	scanf("%d%d",&n,&q);
	scanf("%d%d",&cx,&cy);
	for(int i = 0; i < n; ++ i)
		scanf("%d%d%d%d",&ax[i],&ay[i],&bx[i],&by[i]);
}

void prep()
{
	for(int i = 0; i < n; ++ i)
	{
		int dx = ax[i], dy = ay[i];
		int ex = bx[i], ey = by[i];

		if(dx > ex) swap(dx, ex);
		if(dy > ey) swap(dy, ey);

		int mind = 1e9, maxd = 0;

		// Min - distance

		if(dx <= cx && cx <= ex)
		{
			if(cy < dy) mind = min(mind, dy - cy);
			else if(ey < cy) mind = min(mind, cy - ey);
			else mind = 0;
		}

		if(dy <= cy && cy <= ey)
		{
			if(cx < dx) mind = min(mind, dx - cx);
			else if(ex < cx) mind = min(mind, cx - ex);
		}

		int d1 = abs(dx - cx);
		int d2 = abs(ex - cx);
		int d3 = abs(dy - cy);
		int d4 = abs(ey - cy);

		mind = min(mind, min(d1, d2) + min(d3, d4));
		maxd = max(d1, d2) + max(d3, d4);

		tax[mind] ++;
		tax[maxd+1] --;
	}
}

void solve()
{
	for(int i = 0; i < M; ++ i)
		tax[i] += tax[i-1];

	for(int i = 0, x; i < q; ++ i)
		scanf("%d",&x),printf("%d\n",tax[x]);
}

int main()
{
	freopen("bird.in", "r", stdin);
	freopen("bird.out", "w", stdout);

	init();
	prep();
	solve();

	return 0;
}
