# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
using namespace std;
typedef long long i64;
const int N = 1e3 + 50;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar())<'0' || ch > '9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar())>='0' && ch <='9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
} 
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
} 
i64 qz[N], qz2[N], dp[N], cnt;
int n, low, hi, L[N], M[N];
struct line {
	int x, y;
	long long val;
	bool operator <(const line &tmp) const {
		if(x == tmp.x) return y > tmp.y;
		return x < tmp.x;
	}
}a[N * N];
int main()
{
	freopen("wand.in", "r", stdin);
	freopen("wand.out", "w", stdout);
	Read(n); Read(low); Read(hi);
	for(int i = 1; i <= n; i ++) {
		Read(L[i]);
		qz[i] = qz[i - 1] + L[i];
	}	
	for(int i = 1; i <= n; i ++) {
		Read(M[i]);
		qz2[i] = qz2[i - 1] + M[i];
	}	
	for(int i = 1; i <= n; i ++) {
		for(int j = i; j <= n; j ++) {
			int tmp = qz[j] - qz[i - 1];
			if(tmp >= low && tmp <= hi) {
				a[++cnt].x = i;
				a[cnt].y = j;
				a[cnt].val = qz2[j] - qz2[i - 1];
			}
		}
	}
	sort(a + 1, a + 1 + cnt);
	for(int i = 1; i <= cnt; i ++) {
		for(int j = 1; j < a[i].y; j ++) {
			dp[a[i].y] = max(dp[a[i].y], dp[j] + a[i].val);
		}
	}
	i64 ans = 0;
	for(int i = 1; i <= n; i ++) {
		ans = max(ans, dp[i]);
	}
	print(ans);
	return 0;
}
