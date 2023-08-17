# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
# include <vector>
using namespace std;
const int N = 1e6 + 50, Inf = 0x3f3f3f3f;
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
	if(x < 0) putchar('-');
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
} 
int n, m, K;
int ans1 = Inf, ans2 = Inf;
int _next[2][2] = {{0, 1}, {1, 0}};
vector <int> v[N];
void dfs(int x, int y, int sum1, int sum2)
{
	double tmp1 = (double)sum1 + sum2 * sqrt(2), tmp2 = (double)ans1 + ans2 * sqrt(2);
	if(tmp1 - tmp2 > eps) return;
	if(tmp1 - tmp2 < eps && tmp1 != 0 && x == n && y == m) {
		ans1 = sum1; ans2 = sum2;
	}
	bool flag = false;
	for(int i = 0; i < (int)v[x].size(); i ++) if(v[x][i] == y) {flag = true; break;}
	if(flag) dfs(x + 1, y + 1, sum1, sum2 + 1);
	else {
		for(int i = 0; i < 2; i ++) {
			int dx = x + _next[i][0], dy = y + _next[i][1];
			if(dx < 1 || dx > n || dy < 1 || dy > n) continue;
			dfs(dx, dy, sum1 + 1, sum2);
		}
	}	
	return;
} 
int main()
{
	freopen("fly.in", "r", stdin);
	freopen("fly.out", "w", stdout);
	Read(n); Read(m); Read(K);
	n ++; m ++; 
	for(int i = 1, ui, vi; i <= K; i ++) {
		Read(ui); Read(vi);
		v[ui].push_back(vi);
	}
	ans1 = (n + m);
	dfs(1, 1, 0, 0);
	double tmp = (ans1 + ans2 * sqrt(2)) * 100;
	int ans = (int)tmp;
	bool flag = false;
	if(tmp - ans >= 0.5) flag = 1;
	print(ans + (flag == 1));
	return 0;
}
