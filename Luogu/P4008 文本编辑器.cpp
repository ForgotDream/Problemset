#include <iostream>
#include <cstdio>

using namespace std;

const int N = 2e6 + 50;
int n, pos, optnum;
char opt[10], ch;
int l, r, p;

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
	int val[N], size[N], prm[N], ch[N][2];
	int cnt, root;

	FHQTreap() { cnt = root = 0; };

	void init(int x) {
		return (void)(val[++cnt] = x, prm[cnt] = rand(), size[cnt] = 1, ch[cnt][0] = ch[cnt][1] = 0);
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

	int merge(int l,int r) {
		if (!l || !r) return l + r;
		if (prm[l] > prm[r]) return ch[l][1] = merge(ch[l][1], r), update(l), l;
		else return ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void inorderTraverse(int u) {
		if (!u) return;
		// cerr << u << endl;
		inorderTraverse(ch[u][0]), putchar(val[u]), inorderTraverse(ch[u][1]);
		return;
	}
};

FHQTreap T;

int main() {
	srand(2333);
	read(n);
	while (n--) {
		scanf("%s", opt);
		// cerr << '#' << n << ' ' << opt << endl;
		if (opt[0] == 'I') {
			read(optnum), T.split(T.root, pos, l, r);
			for (int i = 1; i <= optnum; i++) {
				ch = getchar();
				while (ch < 32 || ch > 126) ch = getchar();
				T.init(ch), l = T.merge(l, T.cnt);
				// cout << ch << ' ';
			}
			// cout << endl;
			T.root = T.merge(l, r);
		}
		else if (opt[0] == 'D') {
			read(optnum), T.split(T.root, pos + optnum, l, r), T.split(l, pos, l, p);
			T.root = T.merge(l, r);
		}
		else if (opt[0] == 'G') {
			read(optnum), T.split(T.root, pos + optnum, l, r), T.split(l, pos, l, p);
			T.inorderTraverse(p), putchar('\n');
			T.root = T.merge(T.merge(l, p), r);
		}
		else if (opt[0] == 'M') read(pos);
		else if (opt[0] == 'P') pos--;
		else if (opt[0] == 'N') pos++;
	}
	return 0;
}