# include <cstdio>
# include <iostream>
# include <algorithm>
# include <cstring>
# include <cmath>
using namespace std;
typedef unsigned long long i64;
const int N = 1e5 + 50, Mod = 1e9 + 7;
i64 n, ki, ans, p;
i64 xxx(i64 x, i64 y)
{
	i64 now = 0;
	while(y) {
		if(y & 1) now = (now + x) % Mod;
		x = (x + x) % Mod;
		y >>= 1;
	}
	return now;
}
i64 qpow(i64 x, i64 k)
{
	i64 now = 1;
	while(k) {
		if(k & 1) now = xxx(now, x);
		x = xxx(x, x);
		k >>= 1;
	}
	return now;
}
int main()
{
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n >>ki;
	ans = qpow(ki, ki - 1);
	(ans *= qpow(n - ki, n - ki)) %= Mod;
	cout <<ans;
	return 0;
}