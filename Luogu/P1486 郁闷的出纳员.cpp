#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 1e5 + 50;
int n, m, optnum, minn;
int ans;
char opt[2];

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
	int val[N], size[N], ch[N][2], prm[N];
	// bool del[N];
	int cnt, root, l, r, delta;

	FHQTreap() { cnt = root = 0; };

	void init(int x) {
		return (void)(val[++cnt] = x, size[cnt] = 1, prm[cnt] = rand(), ch[cnt][0] = ch[cnt][1] = 0);
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
		if (!l || !r) return l + r;
		if (prm[l] > prm[r]) return ch[l][1] = merge(ch[l][1], r), update(l), l;
		else return ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void insert(int x) {
		if (x < minn) return;
		x -= delta;
		split(root, x, l, r);
		init(x);
		root = merge(l, merge(cnt, r));
		return;
	}

	void del(int x) {
		delta -= x;
		split(root, minn - delta - 1, l, r);
		root = r;
		ans += size[l];
		return;
	}

	int getNumByRank(int u, int x) {
		if (x == size[ch[u][0]] + 1) return u;
		else if (x > size[ch[u][0]] + 1) return getNumByRank(ch[u][1], x - size[ch[u][0]] - 1);
		else return getNumByRank(ch[u][0], x);
	}

	int getNumByRank(int x) {
		return val[getNumByRank(root, x)];
	}

	void inorderTraverse(int u) {
		if (!u) return;
		inorderTraverse(ch[u][0]), print(size[u], ' '), inorderTraverse(ch[u][1]);
		return;
	}
};

FHQTreap T;

int main() {
	srand(2333);
	read(n, minn);
	while (n--) {
		scanf("%s", opt), read(optnum);
		if (opt[0] == 'I') T.insert(optnum);
		else if (opt[0] == 'A') T.delta += optnum;
		else if (opt[0] == 'S') T.del(optnum);
		else if (opt[0] == 'F') {
			if (T.size[T.root] < optnum) print(-1, '\n');
			else print(T.getNumByRank(T.size[T.root] - optnum + 1) + T.delta, '\n');
			// print(T.getNumByRank(T.size[T.root] - optnum + 1), '\n');
		}
	}
	// T.inorderTraverse(T.root);
	print(ans, '\n');
	return 0;
}