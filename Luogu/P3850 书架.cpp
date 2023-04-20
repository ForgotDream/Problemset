#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <cstdlib>

using namespace std;

const int N = 2e5 + 50;
unordered_map<string, int> mp;
int n, m, rk, all;
string s, str[N];

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

	FHQTreap() { root = 0; };

	int init(int x) {
		return val[++cnt] = x, prm[cnt] = rand(), ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1, cnt;
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

	void insert(int x, int place) {
		int l, r;
		split(root, x, l, r);
		init(place);
		root = merge(l, merge(cnt, r));
		return;
	}

	int getAns(int u) {
		int w, x, y, z, tmp;
		split(root, u, w, x);
		split(x, 1, y, z);
		tmp = y;
		root = merge(w, merge(y, z));
		return tmp;
	}
};

FHQTreap T;

int main() {
	srand(2333);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str[++all];
		T.insert(i - 1, i);
	}
	cin >> m;
	while (m--) {
		cin >> str[++all];
		cin >> rk;
		T.insert(rk, all);
	}
	cin >> m;
	while (m--) {
		cin >> rk;
		cout << str[T.val[T.getAns(rk)]] << endl;
	}
	return 0;
}