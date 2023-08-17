# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
# include <queue>
# include <vector>
using namespace std;
typedef long long i64;
const int N = 4 * 1e4 + 50, Inf = 0x3f3f3f3f, M = 32768;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0;
	while((ch = getchar())<'0' || ch > '9') continue;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) x = -x, putchar('-');
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, m, cnt, hz[N];
struct card {
	int x, y, sum;
	i64 S;
	bool operator <(const card &tmp) const {
		return S * sum < tmp.S * tmp.sum;
	}
} a[30];
struct envelope {
	int x, y, S;
} b[30];
void solve1()
{
	int max1 = 0, max2 = 0;
	for(int i = 1; i <= n; i ++) {
		Read(a[i].x); Read(a[i].y); Read(a[i].sum);
		max1 = max(a[i].x, max1);
		max2 = max(a[i].y, max2);
	}
	i64 ans = 0;
	for(int i = 1; i <= n; i ++) {
		ans += (i64)(max1 * max2 - a[i].x * a[i].y) * (i64)a[i].sum;
	} 
	print(ans);
	return;
}
i64 dp[M << 1];
void solve2()
{
	for(int i = 1; i <= n; i ++) {
		Read(a[i].x); Read(a[i].y); Read(a[i].sum);
		a[i].S = a[i].x * a[i].y;
	}
	sort(a + 1, a + 1 + n);
	for(int i = n; i >= n - m + 2; i --) 
		b[++cnt].x = a[i].x, b[cnt].y = a[i].y, b[cnt].S = a[i].S;
	
	int max1 = 0, max2 = 0;
	for(int i = n - m + 1; i >= 1; i --) {
		max1 = max(a[i].x, max1);
		max2 = max(a[i].y, max2);
	}
	b[++cnt].x = max1; b[cnt].y = max2; b[cnt].S = max1 * max2;
	
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for(int i = 0; i <= (1 << (n - m + 1)) - 1; i ++) {
		for(int j = 1; j <= cnt; j ++) {
			for(int k = 1; k <= n - m + 1; k ++) {
				if(b[j].x >= a[k].x && b[j].y >= a[k].y)
				dp[i | (1 << (k - 1))] = min(dp[i | (1 << (k - 1))], dp[i] + (b[j].S - a[k].S) * a[k].sum);
			}
		}
	}
	print(dp[(1 << (n - m + 1)) - 1]);
	return;
}
int main()
{
	freopen("envelope.in", "r", stdin);
	freopen("envelope.out", "w" , stdout);
	cin >>n >>m;
	if(n == m) {print(0); return 0;}
	if(m == 1) {solve1(); return 0;}
	else solve2();
	return 0;
}
