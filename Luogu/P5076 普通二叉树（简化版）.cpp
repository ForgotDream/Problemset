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
int n;
struct FHQTreap {
	int val[N], prm[N], ch[N][2], size[N];
	int cnt, root;

	FHQTreap() { root = 0; };

	void init(int x) {
		val[++cnt] = x, prm[cnt] = rand();
		ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1;
		return;
	} 

	void update(int u) {
		return (void)(size[u] = size[ch[u][0]] + size[ch[u][1]] + 1);
	}

	void split(int u, int x, int &l, int &r) {
		if (!u) return (void)(l = r = 0);
		if (val[u] <= x) l = u, split(ch[u][1], x, ch[u][1], r);
		else r = u, split(ch[u][0], x, l, ch[u][0]);
		update(u);
		return;
	}

	int merge(int l, int r) {
		if (!l || !r) 
			return l + r;
		if (prm[l] > prm[r]) 
			return ch[l][1] = merge(ch[l][1], r), update(l), l;
		else 
			return ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void insert(int x) {
		int l, r;
		split(root, x, l, r);
		init(x);
		root = merge(merge(l, cnt), r);
		return;
	}

	void del(int x) {
		int l, r, p;
		split(root, x, l, r);
		split(l, x - 1, l, p);
		p = merge(ch[p][0], ch[p][1]), root = merge(merge(l, p), r);
		return;
	}

	int getRankByNum(int x) {
		int l, r, tmp;
		split(root, x - 1, l, r);
		tmp = size[l] + 1;
		root = merge(l, r);
		return tmp;
	}

	int getNumByRank(int u, int x) {
		if (x == size[ch[u][0]] + 1) 
			return u;
		else if (x > size[ch[u][0]] + 1) 
			return getNumByRank(ch[u][1], x - size[ch[u][0]] - 1);
		else return getNumByRank(ch[u][0], x);
	}

	int getPrecursor(int x) {
		int l, r, tmp;
		split(root, x - 1, l, r);
		tmp = val[getNumByRank(l, size[l])];
		root = merge(l, r);
		return tmp;
	}

	int getSuccessor(int x) {
		int l, r, tmp;
		split(root, x, l, r);
		tmp = val[getNumByRank(r, 1)];
		root = merge(l, r);
		return tmp;
	}
} T;

int main() {
	read(n);
	T.insert(2147483647), T.insert(-2147483647);
	for (int i = 1; i <= n; i++) {
		int opt, num;
		read(opt, num);
		if (opt == 1) print(T.getRankByNum(num) - 1, '\n');
		else if (opt == 2) print(T.val[T.getNumByRank(T.root, num + 1)], '\n');
		else if (opt == 3) print(T.getPrecursor(num), '\n');
		else if (opt == 4) print(T.getSuccessor(num), '\n');
		else T.insert(num);
	}
	return 0;
}