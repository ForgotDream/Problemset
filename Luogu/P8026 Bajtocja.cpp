/**
 * @file 	P8026 Bajtocja.cpp
 * @author 	ForgotDream
 * @brief 	Hash + 启发式合并
 * @date 	2023-01-30
 */

#include <bits/stdc++.h>
#include <random>

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
using i64 = long long;
using i64u = unsigned long long;

static const int D = 250, N = 5e3 + 50, MOD = 1e9 + 7;
mt19937 rnd(time(0));
int d, n, m;
int fa[D][N];
i64u val[D][N];
i64 sum[N], ans;
vector<int> ufs[D][N];
unordered_map<i64u, int> mp;

/**
 * @brief 		用于统计答案
 * 
 * @param res 	答案
 * @param hsh 	哈希值，用于维护答案，哈希值相同的可看作联通
 * @param delta 连通或断开
 * @return i64 	新的答案
 */
i64 modify(i64 res, i64 hsh, int delta) {
	res -= mp[hsh] * mp[hsh];
	mp[hsh] += delta;
	res += mp[hsh] * mp[hsh];
	return res;
}

int main() {
	read(d, n, m);

	for (int i = 1; i <= d; i++) 
		for (int j = 1; j <= n; j++) {
			val[i][j] = (i64) rnd() * rnd() % MOD;
			fa[i][j] = j, sum[j] += val[i][j];
			ufs[i][j].push_back(j);
		}

	for (int i = 1; i <= n; i++) 	// 初始化答案
		ans = modify(ans, sum[i], 1);

	while (m--) {
		int x, y, cur;
		read(x, y, cur);
		x = fa[cur][x], y = fa[cur][y];
		
		if (x == y) {	// 特判 x == y
			print(ans, '\n');
			continue;
		}

		if (ufs[cur][x].size() < ufs[cur][y].size()) swap(x, y);	// 启发式合并
		for (int i : ufs[cur][y]) {
			ufs[cur][fa[cur][x]].push_back(i);
			ans = modify(ans, sum[i], -1);
			sum[i] = sum[i] - val[cur][fa[cur][i]] + val[cur][fa[cur][x]];
			ans = modify(ans, sum[i], 1);
			fa[cur][i] = fa[cur][x];
		}

		ufs[cur][y].clear(), print(ans, '\n');
	}
	return 0;
}