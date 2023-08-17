# include <cstdio>
# include <iostream>
# include <cstring>
# include <algorithm>
using namespace std;
const int N = 1e3 + 50;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar()) >='0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x/10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, m, a[N][N], sum[N][N], ans;
int main()
{
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);
	Read(n); Read(m);
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			Read(a[i][j]);
			a[i][j] = (a[i][j] == 0) ? 1 : 0;
			sum[i][j] = sum[i - 1][j] + a[i][j];
		}
	}
	for(int i = 1; i <= n; i ++) {
		for(int j = n; j >= i; j --) {
			int ll = 1, rr = 1;
			while(rr <= m) {
				while(sum[j][rr] - sum[i - 1][rr] != j - i + 1 && rr <= m) rr ++;
				ll = rr;
				while(sum[j][rr] - sum[i - 1][rr] == j - i + 1 && rr <= m) rr ++;
				ans = max(ans, (rr - ll) * (j - i + 1));
			}
		}
	}
	print(ans);
	return 0;
}
