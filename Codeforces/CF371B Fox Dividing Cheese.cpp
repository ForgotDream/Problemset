#include <algorithm>
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

const int M = 1e6 + 50;
int a, b, ans;
int cnt, prime[M];
vector<pair<int, int>> primeCnt[2];
bool isNotPrime[M];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

void divide(int num) {
	static int d = 0;
	int cur = 0;
	for (int i = 1; i <= cnt; i++) {
		int t = 0;
		while (!(num % prime[i])) num /= prime[i], t++;
		primeCnt[d].emplace_back(prime[i], t);
	}
	if (num != 1) primeCnt[d].emplace_back(num, 1);
	d++;
	return;
}

bool check(int num) {
	return (num == 2 || num == 3 || num == 5);
}

int main() {
	getPrime(1e5);

	read(a, b);

	divide(a), divide(b);
	// for (int i = 0; i <= n; i++) 
	if (primeCnt[0].size() != primeCnt[1].size()) print(-1, '\n');
	else {
		for (int i = 0; i < primeCnt[0].size(); i++) {
			if (check(primeCnt[0][i].first)) ans += abs(primeCnt[0][i].second - primeCnt[1][i].second);
			else if (primeCnt[1][i].second != primeCnt[0][i].second || primeCnt[1][i].first != primeCnt[0][i].first) {
				ans = -1;
				break;
			}
		}
		print(ans, '\n');
		// cout << ans << endl;
	}
	return 0;
}
