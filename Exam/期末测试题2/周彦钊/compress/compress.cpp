#include <bits/stdc++.h>

namespace FastIO {
	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using ll = long long;

const int N = 3050;
int n, m;
ll g[N][N], f[N][N], ans = 1e18;

ll calc(ll num) {
    if (!num) return m;
    else if (num == m + 1) return 1;
    else return num;    
}

int main() {
    freopen("compress.in", "r", stdin);
    freopen("compress.out", "w", stdout);
    read(n, m);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) 
            read(g[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f[i][j] = min(f[i - 1][calc(j - 1)], min(f[i - 1][j], f[i - 1][calc(j + 1)])) + g[i][j];
    for (int j = 1; j <= m; j++) ans = min(ans, f[n][j]);
    print(ans, '\n');
    return 0;
}
