# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
# include <vector>
using namespace std;
const int N = 1e5, Inf = 0x3f3f3f3f;
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
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
} 
int n, M, T;
int a[N], ans[N];
int main()
{
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);
	Read(n); Read(M); Read(T);
	for(int i = 1; i <= n; i ++) Read(a[i]);
	int k = (T + M - 1) % n, cnt = 0;
	for(int i = k + n; i >= k; i --) {
		ans[++cnt] = a[(i - 1) % n + 1];
	}
	for(int i = 1; i <= n; i ++) {
		print(ans[i]); putchar(' ');
	}
	return 0; 
}

