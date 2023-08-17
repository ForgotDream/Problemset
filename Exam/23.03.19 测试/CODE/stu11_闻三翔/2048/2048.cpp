# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 1e5 + 50, Mod = 998244353;
template <class T> inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
} 
template <typename T> inline
void print(T x)
{
	if(x < 0) x = -x, putchar('-');
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int p[20] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
int id[2000], cnt[20];
bool vis[N];
int ans, n, a[N], tot;
i64 qpow(i64 x, i64 k)
{
	i64 now = 1;
	while(k) {
		if(k & 1) (now *= x) %= Mod; 
		(x *= x) %= Mod;
		k >>= 1;
	}
	return now;
}
long long dp[5000];
void dfs(int now, int pre)
{
	if(now >= 2048) {
		ans += qpow(2, n - pre + 1);
		return; 
	}
	for(int i = pre; i <= tot; i ++) {
		if(vis[i]) continue;
		vis[i] = 1;
		dfs(now + (1 << id[a[i]]), i + 1);
		vis[i] = 0;
	}
	return;
}
int main()
{
	freopen("2048.in", "r", stdin);
	freopen("2048.out", "w", stdout);
	for(int i = 0; i <= 11; i ++) {
		id[p[i]] = i;
	}
	Read(n);
	for(int i = 1, x; i <= n; i ++) {
		Read(x);
		a[++ tot] = x;
		cnt[id[x]] ++;
	}
	sort(a + 1, a + 1 + n);
	dp[0] = 1;
	for(int i = 1; i <= n; i ++) {
		if(id[a[i]] == 0 && a[i] != 1) {
			continue;
		}
		for(int j = 2048; j >= 0; j --) {
			int tmp = j + a[i];
			if(j + a[i] > 2048) tmp = 2048;
			(dp[tmp] += dp[j]) %= Mod;
		}
	}
	print(dp[2048]);
 	return 0;
}
