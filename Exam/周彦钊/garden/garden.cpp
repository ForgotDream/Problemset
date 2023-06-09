#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  struct Node {
    int val;
    int lc, rc, l, r;
    Node() { val = lc = rc = l = r = 0; }
  };
  std::vector<Node> tree;
  std::unordered_map<int, int> root;
  std::stack<int> pool;
  std::vector<int> col;

  SegTree(int _n, const std::vector<int> &_col) {
    n = _n, col = _col;
    tree.resize((n << 5) + 1);
    for (int i = n << 5; i; i--) { pool.push(i); }
  }

  void pushup(int u) {
    tree[u].val = tree[tree[u].lc].val + tree[tree[u].rc].val;
  }

  int init(int l, int r) {
    int cur = pool.top();
    tree[cur].l = l, tree[cur].r = r;
    pool.pop();
    return cur;
  }

  void del(int u) {
    pool.push(u);
    Node &cur = tree[u];
    cur.l = cur.r = cur.lc = cur.rc = cur.val = 0;
  }

  void build() {
    for (int i = 0; i < n; i++) {
      int cur = col[i];
      if (!root.count(cur)) { root[cur] = init(1, n); }
      add(i + 1, root[cur]);
    }
  }

  void add(int target, int &u) {
    int s = tree[u].l, t = tree[u].r;
    if (s == target && t == target) {
      tree[u].val = 1;
      return;
    }
    int mid = (s + t) >> 1, &lc = tree[u].lc, &rc = tree[u].rc;
    if (target <= mid) {
      if (!lc) { lc = init(s, mid); }
      add(target, lc);
    } else {
      if (!rc) { rc = init(mid + 1, t); }
      add(target, rc);
    }
    pushup(u);
  }

  bool erase(int target, int &u) {
    int s = tree[u].l, t = tree[u].r;
    if (s == target && t == target) {
      del(u);
      return true;
    }
    int mid = (s + t) >> 1, &lc = tree[u].lc, &rc = tree[u].rc;
    if (target <= mid) {
      if (erase(target, lc)) { lc = 0; }
    } else {
      if (erase(target, rc)) { rc = 0; }
    }
    if (!lc && !rc) {
      del(u);
      return true;
    } else {
      pushup(u);
      return false;
    }
  }

  void modify(int target, int val) {
    int pre = col[target - 1];
    if (erase(target, root[pre])) { root.erase(pre); }
    col[target - 1] = val;
    if (!root.count(val)) { root[val] = init(1, n); }
    add(target, root[val]);
  }

  int _query(int l, int r, int u) {
    int s = tree[u].l, t = tree[u].r;
    if (l <= s && t <= r) {
      return tree[u].val;
    }
    int mid = (s + t) >> 1, lc = tree[u].lc, rc = tree[u].rc;
    int res = 0;
    if (mid >= l && lc) {
      res += _query(l, r, lc);
    }
    if (mid < r && rc) {
      res += _query(l, r, rc);
    }
    return res;
  }

  int query(int l, int r, int col) {
    if (!root.count(col) || !root[col]) { return 0; }
    return _query(l, r, root[col]);
  }
};

namespace zyz {
	int n, q, clk;
	std::vector<std::vector<int>> adj;
	std::vector<int> siz, dep, son, fa;
	std::vector<int> idx, top;
	
	void init() {
		adj.resize(n + 1);
		siz.resize(n + 1);
		dep.resize(n + 1);
		son.resize(n + 1);
		fa.resize(n + 1);
		idx.resize(n + 1);
		top.resize(n + 1);
	}
	
	void dfs1(int u, int frm) {
		dep[u] = dep[frm] + 1, siz[u] = 1, fa[u]= frm;
		// std::cerr << dep[u] << " " << u << " " << frm << "\n";
		for (auto v : adj[u]) {
			if (v == frm) { continue; }
			dfs1(v, u);
			siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) {
				son[u] = v;
			}
		}
	}
	
	void dfs2(int u, int rt) {
		idx[u] = ++clk, top[u] = rt;
    if (son[u]) { dfs2(son[u], rt); }
    for (auto v : adj[u]) {
      if (v == fa[u] || v == son[u]) { continue; }
      dfs2(v, v);
    }
	}
}

using namespace zyz;

int main() {
  freopen("garden.in", "r", stdin);
  freopen("garden.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> q;

	init();

  std::vector<int> t(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> t[i];
  }

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs1(1, 0);
	dfs2(1, 1);

  std::vector<int> a(n);
  for (int i = 1; i <= n; i++) {
    a[idx[i] - 1] = t[i];
  }

  SegTree st(n, a);
  st.build();

  auto queryP2P = [&](int u, int v, int col) {
    int res = 0;

    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) { std::swap(u, v); }
      res += st.query(idx[top[u]], idx[u], col);
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) { std::swap(u, v); }
    res += st.query(idx[u], idx[v], col);

    return res;
  };

  int lst = 0;
  while (q--) {
    char opt;
    std::cin >> opt;

    if (opt == 'C') {
      int u, col;
      std::cin >> u >> col;
      u ^= lst, col ^= lst;
      st.modify(idx[u], col);
    } else {
      int u, v, col;
      std::cin >> u >> v >> col;
      u ^= lst, v ^= lst, col ^= lst;
      lst = queryP2P(u, v, col);
      std::cout << lst << "\n";
    }
  }

  return 0;
}