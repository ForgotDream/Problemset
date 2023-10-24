#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e5 + 50;
char ch;
int q, n, opt, x, y;

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
	int cnt, root;
	int l, r, p;

	FHQTreap() { root = 0; };

	void init(int x) {
		return (void)(val[++cnt] = x, prm[cnt] = rand(), ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1);
	}

	void update(int u) {
		return (void)(size[u] = size[ch[u][0]] + size[ch[u][1]] + 1);
	}

	void split(int u, int x, int &l, int &r) {
		if (!u) return (void)(l = r = 0);
		if (size[ch[u][0]] < x) l = u, split(ch[u][1], x - size[ch[u][0]] - 1, ch[u][1], r);
		else r = u, split(ch[u][0], x, l, ch[u][0]);
		update(u);
		return;
	}

	int merge(int l, int r) {
		if (!l || !r) return l + r;
		if (prm[l] > prm[r]) return ch[l][1] = merge(ch[l][1], r), update(l), l;
		else return ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void insert(int x) {
		init(x), root = merge(root, cnt);
		return;
	}

	void moveToFront(int x, int y) {
		split(root, y, l, r), split(l, x - 1, l, p);
		root = merge(merge(p, l), r);
		return;
	}

	void moveToBack(int x, int y) {
		split(root, y, l, r), split(l, x - 1, l, p);
		root = merge(merge(l, r), p);
		return;
	}

	char query(int x) {
		split(root, x, l, r), split(l, x - 1, l, p);
		int tmp = p;
		root = merge(merge(l, p), r);
		return val[p];
	}

	void inorderTraverse(int u) {
		if (!u) return;
		inorderTraverse(ch[u][0]), putchar(val[u]), inorderTraverse(ch[u][1]);
		return;
	}
};

FHQTreap T;

int main() {
	ch = getchar();
	while (isalpha(ch)) T.insert(ch), ch = getchar();
	read(q); 
	while (q--) {
		read(opt);
		if (opt == 1) read(x, y), T.moveToFront(x + 1, y + 1);
		else if (opt == 2) read(x, y), T.moveToBack(x + 1, y + 1);
		else read(x), putchar(T.query(x + 1)), putchar('\n');
	}
	// T.inorderTraverse(T.root), putchar('\n');
	// T.moveToBack(2, 3);
	// T.inorderTraverse(T.root);
	// cerr << T.query(1) << endl;
	// cerr << T.query(2) << endl;
	return 0;
}