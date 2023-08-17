# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 1e4 + 50, M = 1e8 + 5;

template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
} 
template <typename T>inline
void print(T x)
{
	if(x < 0) {putchar('-'); x = -x;}
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}

int cnt[5], n;
i64 a[5][N];
int f[M];
i64 ans;
void dfs1(int step, int sum)
{
	if(step > 2) {
		f[sum] ++;
		return;
	}
	for(int i = 1; i <= cnt[step]; i ++) {
		if(sum + a[step][i] <= n) {
			dfs1(step + 1, sum + a[step][i]);
		}
	}
	return;
}
void dfs2(int step, int sum)
{
	if(step > 4) {
		ans += f[n - sum];
		return;
	}
	for(int i = 1; i <= cnt[step]; i ++) {
		if(sum + a[step][i] <= n) {
			dfs2(step + 1, sum + a[step][i]);
		}
	}
	return;
}
int main()
{
	freopen("eat.in", "r", stdin);
	freopen("eat.out", "w", stdout);
	Read(n); Read(cnt[1]); Read(cnt[2]); Read(cnt[3]); Read(cnt[4]);
	for(int i = 1; i <= 4; i ++) {
		for(int j = 1; j <= cnt[i]; j ++) {
			Read(a[i][j]);
		}
	}
	dfs1(1, 0);
	for(int i = 1; i <= n; i ++) {
		f[i] += f[i - 1];
	}
	dfs2(3, 0);
	cout <<ans;
	return 0;
}
