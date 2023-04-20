/**
 * @file 	P4397 聪明的燕姿.cpp
 * @author 	ForgotDream
 * @brief 	唯一分解定理 + 搜索
 * @date 	2023-01-29
 */

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
using i64 = long long;
using i128 = __int128;

const int N = 1e6 + 50;
int primeCnt, prime[N];
bool isNotPrime[N];
int ans[N], ansCnt, n;

void getPrime(int n) {
	isNotPrime[1] = true;
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++primeCnt] = i;
		for (int j = 1; j <= primeCnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
	return;
}

bool isPrime(int n) {
	if (n <= 1e5) return !isNotPrime[n];
	for (int i = 1; (i64) prime[i] * prime[i] <= n; i++)
		if (!(n % prime[i])) return false;
	return true;
}

/**
 * @brief 		核心部分，分解原数并统计，用到了唯一分解定理
 * 
 * @param cur 	当前数字
 * @param cnt 	当前用到第几个质数
 * @param rst 	原数剩余部分
 */
void dfs(i64 cur, int cnt, int rst) {
	if (rst == 1) return (void) (ans[++ansCnt] = cur);
	if (rst > prime[cnt] && isPrime(rst - 1)) ans[++ansCnt] = (rst - 1) * cur;
	for (int i = cnt; i <= primeCnt && (i64) prime[i] * prime[i] <= rst; i++) {
		// 唯一分解
		i64 tmp = prime[i], all = prime[i] + 1;
		for (; all <= rst; tmp *= prime[i], all += tmp) {
			if (!(rst % all)) dfs(cur * tmp, i + 1, rst / all);
		}
	}
	return;
}

int main() {
	getPrime(1e5);
	while (cin >> n) {
		ansCnt = 0;
		dfs(1, 1, n);
		cout << ansCnt << '\n';
		if (!ansCnt) continue;
		sort(ans + 1, ans + ansCnt + 1);
		for (int i = 1; i <= ansCnt; i++) cout << ans[i] << ' ';
		cout << '\n';
	}
	return 0;
}