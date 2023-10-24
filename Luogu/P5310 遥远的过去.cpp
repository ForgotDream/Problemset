#include <bits/stdc++.h>
#include <unordered_map>

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
using ull = unsigned long long;

const int N = 1e7 + 50, BASE = 131;
int n, m, q;
int a[N], b[N];
ull base[N];
struct FHQTreap {
	int val[N], prm[N], ch[N][2], size[N], lzy[N], power[N];
	ull hash[N], sum[N];
	int cnt, root;

	FHQTreap() { root = 0; };

	void init(int x, int y) {
		val[++cnt] = x, prm[cnt] = rand(), power[cnt] = y, hash[cnt] = base[y], sum[cnt] = base[y];
		ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1;
		return;
	} 

	void update(int u) {
		size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
		sum[u] = sum[ch[u][0]] + sum[ch[u][1]] + base[power[u]];
		hash[u] = hash[ch[u][0]] + (size[ch[u][0]] + 1) * base[power[u]] + hash[ch[u][1]] + (size[ch[u][0]] + 1) * sum[ch[u][1]];
		return;
	}

	void pushdown(int u) {
		if (!lzy[u]) return;
		lzy[ch[u][0]] += lzy[u], lzy[ch[u][1]] += lzy[u];
		power[ch[u][0]] += lzy[u], power[ch[u][1]] += lzy[u];
		sum[ch[u][0]] *= base[lzy[u]], sum[ch[u][1]] *= base[lzy[u]];
		hash[ch[u][0]] *= base[lzy[u]], hash[ch[u][1]] *= base[lzy[u]];
		lzy[u] = 0;
		return;
	}

	void split(int u, int x, int &l, int &r) {
		if (!u) return (void)(l = r = 0);
		pushdown(u);
		if (size[ch[u][0]] < x) l = u, split(ch[u][1], x - size[ch[u][0]] - 1, ch[u][1], r);
		else r = u, split(ch[u][0], x, l, ch[u][0]);
		update(u);
		return;
	}

	int merge(int l, int r) {
		if (!l || !r) 
			return l + r;
		if (prm[l] > prm[r]) 
			return pushdown(l), ch[l][1] = merge(ch[l][1], r), update(l), l;
		else 
			return pushdown(r), ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	int getRankByNum(int u, int x) {
		if (!u) return 0;
		pushdown(u);
		if (val[u] < x) return size[ch[u][0]] + 1 + getRankByNum(ch[u][1], x);
		else return getRankByNum(ch[u][0], x);
	}

	void insert(int x, int y) {
		int l, r, tmp;
		split(root, tmp = getRankByNum(root, x), l, r);
		// cerr << '$' << x << ' ' << tmp << endl;
		init(x, y);
		root = merge(merge(l, cnt), r);
		return;
	}

	void del(int x) {
		int l, r, p;
		int tmp = getRankByNum(root, x);
		// cerr << '#' << x << ' ' << tmp << endl;
		split(root, tmp, l, r);
		split(r, 1, p, r);
		p = merge(ch[p][0], ch[p][1]), root = merge(merge(l, p), r);
		return;
	}

	void add() {
		lzy[root] += 1;
		power[root] += 1;
		sum[root] *= base[1];
		hash[root] *= base[1];
		return;
	}

	ull getHash() {
		return hash[root];
	}

	void out1(int u) {
		if (!u) return;
		out1(ch[u][0]);
		print(val[u], ' ');
		out1(ch[u][1]);
	}
} T, T2;
unordered_map<ull, int> mp;

int main() {
	// 用 FHQ 来维护 a 中一个长为 m 的字符串，按排名分裂
	srand(time(nullptr));
	
	read(n, m, q);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1; i <= m; i++) read(b[i]);

	base[0] = 1;
	for (int i = 1; i <= m; i++) base[i] = base[i - 1] * BASE;

	// T.insert(0, 0);
	for (int i = 1; i <= m; i++) T.insert(a[i], m - i);
	mp[T.getHash()] = 1;
	// cerr << T.getHash() << endl;
	for (int i = m + 1; i <= n; i++) 
		T.del(a[i - m]), T.add(), T.insert(a[i], 0), mp[T.getHash()]++;
	
	// for (auto it : mp) cerr << it.first << ' ' << it.second << endl;

	// print(T.getRankByNum(T.root, 2), '\n');
	// T.out1(T.root);

	for (int i = 1; i <= m; i++) T2.insert(b[i], m - i);
	while (q--) {
		int x, y;
		read(x, y);
		T2.del(b[x]), T2.insert(b[x] = y, m - x);
		print(mp[T2.getHash()], '\n');
		// cerr << T2.getHash() << endl;
	}
	return 0;
}
