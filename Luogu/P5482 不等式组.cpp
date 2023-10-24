#include <bits/stdc++.h>

namespace FastIO {
	char buf[1 << 23], *p1 = buf, *p2 = buf;

	inline char gc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
	}

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

const int N = 1e5 + 50, M = 1e6 + 50;
int n, tree[2 * M][2], type[N], val[N];
int num, cnt;
bool del[N];

inline int lowbit(int x) {
	return x & -x;
}

inline void add(int u, int num, int type) {
	u += 1e6 + 20;
	for (int i = u; i <= 2e6 + 20; i += lowbit(i)) 
		tree[i][type] += num;
	return;
}

inline int query(int u, int type) {
	int res = 0;
	u += 1e6 + 20;
	for (int i = u; i; i -= lowbit(i)) 
		res += tree[i][type];
	return res;
}

int main() {
	// type <- 1: >; type <- 2: <; type <- 3: ==; type <- 4: !=;
	// Build two BIT presenting the two types of the inequality
	char opt[10];
	read(n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", opt);
		int a, b, c;
		if (opt[0] == 'A') {
			read(a, b, c);
			if (!a) {
				if (b > c) num++, type[++cnt] = 3;   // 恒成立
				else type[++cnt] = 4;   // 恒不成立
			} else if (a > 0) {
				val[++cnt] = floor((double) (c - b) / a);
				if (val[cnt] > 1e6) type[cnt] = 4;
				else if (val[cnt] < -1e6) type[cnt] = 3, num++;
				else type[cnt] = 1, add(val[cnt], 1, 1);
			} else {
				val[++cnt] = ceil(double (c - b) / a);
				if (val[cnt] < -1e6) type[cnt] = 4;
				else if (val[cnt] > 1e6) type[cnt] = 3, num++;
				else type[cnt] = 2, add(val[cnt], 1, 0);
			}
		} 
		else if (opt[0] == 'Q') 
			read(a), print(query(a - 1, 1) + query(1e6, 0) - query(a, 0) + num, '\n');
		else {
			read(a);
			if (del[a]) continue;
			del[a] = true;
			if (type[a] == 1) add(val[a], -1, 1);
			else if (type[a] == 2) add(val[a], -1, 0);
			else if (type[a] == 3) num--;
		}
	}
	return 0;
}