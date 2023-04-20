#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 1e5 + 50;
int n, opt, optnum;

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

struct Treap {
	int val[N], prm[N], ch[N][2], size[N];
	int cnt, root;

	Treap() { root = 0; };

	void init(int u) {
		val[++cnt] = u, prm[cnt] = rand(), ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1;
		return;
	}

	void update(int u) {
		size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
		return;
	}

	void rotate(int &u, int d) {
		int k = ch[u][d];
		ch[u][d] = ch[k][d ^ 1];
		ch[k][d ^ 1] = u;
		size[k] = size[u];
		update(u), u = k;
		return;
	}

	void insert(int &u, int x) {
		if (!u) return (void)(init(x), u = cnt);
		size[u]++;
		if (x >= val[u]) insert(ch[u][1], x);
		else insert(ch[u][0], x);
		if (ch[u][0] && prm[u] > prm[ch[u][0]]) rotate(u, 0);
		if (ch[u][1] && prm[u] > prm[ch[u][1]]) rotate(u, 1);
		update(u);
		return;
	}

	void del(int &u, int x) {
		size[u]--;
		if (val[u] == x) {
			if (!ch[u][0] && !ch[u][1]) return (void)(u = 0);
			if (!ch[u][0] || !ch[u][1]) return (void)(u = ch[u][0] + ch[u][1]);
			if (prm[ch[u][0]] < prm[ch[u][1]]) return (void)(rotate(u, 0), del(ch[u][1], x));
			else (void)(rotate(u, 1), del(ch[u][0], x));
		} else {
			if (val[u] >= x) del(ch[u][0], x);
			else del(ch[u][1], x);
			update(u);
			return;
		}
	}

	int getRankByNum(int u, int x) {
		if (!u) return 0;
		if (x > val[u]) return size[ch[u][0]] + getRankByNum(ch[u][1], x) + 1;
		return getRankByNum(ch[u][0], x);
	}

	int getNumByRank(int u, int x) {
		if (x == size[ch[u][0]] + 1) return val[u];
		if (x > size[ch[u][0]] + 1) return getNumByRank(ch[u][1], x - size[ch[u][0]] - 1);
		// if (x <= size[ch[u][0]]) return getNumByRank(ch[u][0], x);
		return getNumByRank(ch[u][0], x);
	}

	int getPrecursor(int u, int x) {
		if (!u) return 0;
		if (val[u] >= x) return getPrecursor(ch[u][0], x);
		int tmp = getPrecursor(ch[u][1], x);
		return (tmp ? tmp : val[u]);
	}

	int getSuccessor(int u, int x) {
		if (!u) return 0;
		if (val[u] <= x) return getSuccessor(ch[u][1], x);
		int tmp = getSuccessor(ch[u][0], x);
		return (tmp ? tmp : val[u]);
	}
};

Treap T;

int main() {
	srand(time(0));
	read(n);
	while (n--) {
		read(opt, optnum);
		if (opt == 1) T.insert(T.root, optnum);
		else if (opt == 2) T.del(T.root, optnum);
		else if (opt == 3) print(T.getRankByNum(T.root, optnum) + 1, '\n');
		else if (opt == 4) print(T.getNumByRank(T.root, optnum), '\n');
		else if (opt == 5) print(T.getPrecursor(T.root, optnum), '\n');
		else print(T.getSuccessor(T.root, optnum), '\n');
	}
	return 0;
}