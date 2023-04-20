#include <iostream>
#include <cstdio>

using namespace std;

const int N = 5e4 + 50;
int n, m;
int opt, x, y, z;

template<typename T>
void read(T& x) {
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
void read(T& x, args& ... tmp) {
	read(x);
	read(tmp...);
	return;
}

template<typename T>
void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x / 10) print(x / 10);
	putchar(x % 10 + '0');
	return;
}

template<typename T>
void print(T x, char c) {
	print(x), putchar(c);
	return;
}

struct FHQTreap {
	int val[N], prm[N], ch[N][2], size[N], maxx[N], add[N];
	bool rev[N];
	int cnt, root;
	int l, r, p;

	FHQTreap() { root = 0; };

	void init(int x) {
		return (void)(val[++cnt] = x, prm[cnt] = rand(), ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1, maxx[cnt] = x);
	}

	void update(int u) {
		size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
		maxx[u] = val[u];
		if (ch[u][0]) maxx[u] = max(maxx[u], maxx[ch[u][0]]);
		if (ch[u][1]) maxx[u] = max(maxx[u], maxx[ch[u][1]]);
		return;
	}

	void pushdown(int u) {
		if (rev[u]) swap(ch[u][0], ch[u][1]), rev[ch[u][0]] ^= 1, rev[ch[u][1]] ^= 1, rev[u] = false;
		if (add[u]) {
			if (ch[u][0]) add[ch[u][0]] += add[u], maxx[ch[u][0]] += add[u], val[ch[u][0]] += add[u];
			if (ch[u][1]) add[ch[u][1]] += add[u], maxx[ch[u][1]] += add[u], val[ch[u][1]] += add[u]; 
			add[u] = 0, update(u);
		}
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
		if (!l || !r) return l + r;
		if (prm[l] > prm[r]) return pushdown(l), ch[l][1] = merge(ch[l][1], r), update(l), l;
		else return pushdown(r), ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void inorderTraverse(int u) {
		if (!u) return;
		pushdown(u);
		inorderTraverse(ch[u][0]), print(val[u], ' '), inorderTraverse(ch[u][1]);
		return;
	}

	void reverse(int x, int y) {
		split(root, y, l, r);
		split(l, x - 1, l, p);
		rev[p] ^= 1;
		root = merge(merge(l, p), r);
		return;
	}

	void modify(int x, int y, int num) {
		split(root, y, l, r), split(l, x - 1, l, p);
		add[p] += num, val[p] += num, maxx[p] += num;
		root = merge(merge(l, p), r);
		return;
	}

	int query(int x, int y) {
		split(root, y, l, r), split(l, x - 1, l, p);
		int tmp = maxx[p];
		root = merge(merge(l, p), r);
		return tmp;
	}
};

FHQTreap T;

int main() {
	read(n, m);

	for (int i = 1; i <= n; i++) T.init(0), T.root = T.merge(T.root, T.cnt);

	while (m--) {
		read(opt);
		if (opt == 1) read(x, y, z), T.modify(x, y, z);
		else if (opt == 2) read(x, y), T.reverse(x, y);
		else read(x, y), print(T.query(x, y), '\n');
	}

	return 0;
}