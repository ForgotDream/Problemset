#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e5 + 50;
int n, m, x, y;

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
	int val[N], prm[N], ch[N][2], size[N];
	bool rev[N];
	int cnt, root;
	int l, r, p;

	FHQTreap() { root = 0; };

	void init(int x) {
		return (void)(val[++cnt] = x, prm[cnt] = rand(), ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1);
	}

	void update(int u) {
		return (void)(size[u] = size[ch[u][0]] + size[ch[u][1]] + 1);
	}

	void pushdown(int u) {
		if (!rev[u]) return;
		swap(ch[u][0], ch[u][1]), rev[ch[u][0]] ^= 1, rev[ch[u][1]] ^= 1;
		rev[u] = false;
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

	void inOrderTraverse(int u) {
		if (!u) return;
		pushdown(u);
		inOrderTraverse(ch[u][0]), print(val[u], ' '), inOrderTraverse(ch[u][1]);
		return;
	}

	void modify(int x, int y) {
		split(root, y, l, r);
		split(l, x - 1, l, p);
		rev[p] ^= 1;
		root = merge(merge(l, p), r);
		return;
	}
};

FHQTreap T;

int main() {
	read(n, m);
	for (int i = 1; i <= n; i++) T.init(i), T.root = T.merge(T.root, T.cnt);
	while (m--) {
		read(x, y);
		T.modify(x, y);
	}
	T.inOrderTraverse(T.root);
	return 0;
}