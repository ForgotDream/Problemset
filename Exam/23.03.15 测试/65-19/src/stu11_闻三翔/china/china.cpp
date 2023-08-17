# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 1e5 + 50;
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
i64 ans, s, n, l, r, v;
int main()
{
	freopen("china.in", "r", stdin);
	freopen("china.out", "w", stdout);
	Read(s); Read(n);
	ans = s;
	for(int i = 1; i <= n; i ++) {
		Read(l); Read(r); Read(v);
		ans += (r - l + 1) * (v - 1);
	}
	print(ans);
	return 0;
}
