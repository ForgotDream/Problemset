# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 1e5 + 50;
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
i64 a, b, ans;
int T;
void solve()
{
	if(a > b) swap(a, b);
	i64 k = b / a;
	if(b % a == 0) k --;
	b -= k * a;
	ans += k;
	return;
}
int main()
{
	freopen("sword.in", "r", stdin);
	freopen("sword.out", "w", stdout);
	Read(T);
	while(T --) {
		ans = 0;
		Read(a); Read(b);
		while(a != b) {
			solve();
		}
		print(ans); 
		putchar('\n');
	}
	return 0;
}
/*
3
1 8
3 7
6 6
*/
/*
2
2131312231232232 2
36471211727171171 2312312312111
*/
