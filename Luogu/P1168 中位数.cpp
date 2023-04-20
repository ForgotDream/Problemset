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
using Edge = pair<int, int>;

const int N = 1e5 + 50;
priority_queue<int, vector<int>, less<int>> big;
priority_queue<int, vector<int>, greater<int>> small;
int n, a[N];

void maintain(int k) {
	if (small.size() > k)
		while (small.size() > k) big.push(small.top()), small.pop();
	if (small.size() < k)
		while (small.size() < k) small.push(big.top()), big.pop();
	return;
}

void add(int num, int k) {
	if (small.empty() || num > small.top()) small.push(num);
	else big.push(num);
	maintain(k);
	return;
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]), add(a[i], (i >> 1) + (i & 1));
		if (i & 1) maintain((i >> 1) + (i & 1)), print(small.top(), '\n');
	}
	return 0;
}