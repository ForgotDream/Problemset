# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
using namespace std;
const int N = 1e5 + 50, Inf = 0x3f3f3f3f, Mod = 1e9 + 7;
typedef unsigned long long i64;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar())<'0' || ch >'9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar())>='0' && ch <='9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base;
	return;
}
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x /10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
}
i64 n, a[N], ans, p[N], qz[N];
int main()
{
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
	Read(n);  p[0] = 1; Read(a[0]); a[0] %= Mod;
	for(int i = 1; i <= n; i ++) {
		Read(a[i]); a[i] %= Mod;
		p[i] = p[i - 1] * 2 % Mod;
	}	
	p[n + 1] = p[n] * 2 % Mod;
	for(int i = n; i >= 1; i --) 
		qz[i] = (qz[i + 1] + a[i] * p[n - i + 1] % Mod) % Mod;
	for(int i = 0; i <= n; i ++) {
		ans = (ans + a[i] * qz[i + 1] % Mod) % Mod;
	}
	print(ans % Mod);
	return 0;
} 

