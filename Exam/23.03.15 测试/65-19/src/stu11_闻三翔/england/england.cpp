# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 1e5 + 50, Inf = 0x3f3f3f3f;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar()) < '0' || ch > '9') base = (ch == '-') ? -1 : 1;
	x += ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) {x = -x; putchar('-');}
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
int n, a[N], maxn, b[N], ans, len[N];
int main()
{
	freopen("england.in", "r", stdin);
	freopen("england.out", "w", stdout);
	Read(n); 
	for(int i = 1; i <= n; i ++) Read(a[i]);
	int rr = 0;
	for(int i = 1; i <= n; i ++) {
		while(a[b[rr]] >= a[i] && rr > 0) rr --;
		b[++ rr] = i;
		for(int j = 1; j <= rr; j ++) {
			ans = max(ans, a[b[j]] * (b[rr] - b[j - 1]));
		}	
	}
	print(ans);
	return 0;
}
