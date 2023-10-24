#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 50;
struct FHQTreap {
	vector<int> val, prm, size, rev;
	vector<vector<int>> ch;
 	int cnt, root;
	int l, r, p;

	FHQTreap() { 
		val.push_back(0), prm.push_back(0), size.push_back(0), rev.push_back(false);
		ch.push_back(vector<int>(2, 0));
		root = 0; 
	};

	void init(int x) {
		val.push_back(x), prm.push_back(rand()), size.push_back(1), rev.push_back(0);
		ch.push_back(vector<int>(2, 0)), cnt++;
		return;
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
		if (size[ch[u][0]] < x) 
			l = u, split(ch[u][1], x - size[ch[u][0]] - 1, ch[u][1], r);
		else r = u, split(ch[u][0], x, l, ch[u][0]);
		update(u);
		return;
	}

	int merge(int l, int r) {
		if (!l || !r) 
			return l + r;
		if (prm[l] > prm[r]) 
			return pushdown(l), ch[l][1] = merge(ch[l][1], r), update(l), l;
		else return pushdown(r), ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void inorderTraverse(int u) {
		if (!u) return;
		pushdown(u);
		inorderTraverse(ch[u][0]); 
		// putchar(val[u]); 
		cout << (char) val[u];
		inorderTraverse(ch[u][1]);
		return;
	}

	void modify(int x, int y) {
		split(root, y, l, r);
		split(l, x - 1, l, p);
		rev[p] ^= 1;
		root = merge(merge(l, p), r);
		return;
	}

	int query(int x) {
		split(root, x + 1, l, r), split(l, x, l, p);
		int res = val[p];
		root = merge(merge(l, p), r);
		return res;
	}
};
FHQTreap line, row;
int h, w, q;
vector<vector<char>> e;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> h >> w;
	
	e.resize(h + 1);
	for (int i = 1; i <= h; i++) {
		e[i].resize(w + 1);
		for (int j = 1; j <= w; j++) cin >> e[i][j];
	}

	for (int i = 1; i <= h; i++) line.init(i), line.root = line.merge(line.root, line.cnt);
	for (int i = 1; i <= w; i++) row.init(i), row.root = row.merge(row.root, row.cnt);

	cin >> q;
	while (q--) {
		int x, y;
		cin >> x >> y;
		line.modify(1, x), line.modify(x + 1, h);
		row.modify(1, y), row.modify(y + 1, w);
	}

	for (int i = 0; i < h; i++) { 
		for (int j = 0; j < w; j++) {
			int x = line.query(i), y = row.query(j);
			cout << e[x][y];
		}
		cout << endl;
	}
	return 0;
}