/**
 * @file    P2161 会场预约.cpp
 * @author  ForgotDream
 * @brief   BST
 * @date    2023-05-30
 */
#include <bits/stdc++.h>

using i64 = long long;

template<typename T = int>
struct FHQTreap {
  std::mt19937 rnd;
  struct Node {
    int lc, rc;
    int siz, prm;
    T val[2];
  };
  std::vector<Node> tree;
  int cnt, root;
  FHQTreap(int _n = 0) {
    rnd = std::mt19937(
      std::chrono::system_clock::now().time_since_epoch().count()
    );
    tree.resize(_n);
    cnt = 0, root = 0;
  };
  bool empty() { return tree[root].siz == 0; }
  int size() { return tree[root].siz; }
  void pushup(int u) { 
    tree[u].siz = tree[tree[u].lc].siz + tree[tree[u].rc].siz + 1;
  }
  int init(T l, T r) {
    if (cnt == tree.size() - 1) {
      tree.resize(std::max(1.5 * tree.size(), 10.));
    }
    tree[++cnt].val[0] = l, tree[cnt].val[1] = r;
    tree[cnt].prm = rnd(), tree[cnt].siz = 1;
    tree[cnt].lc = tree[cnt].rc = 0;
    return cnt;
  }
  void split(int u, T val, int &l, int &r, int d) {
    if (!u) {
      l = r = 0;
      return;
    }
    if (tree[u].val[d] < val) {
      l = u, split(tree[u].rc, val, tree[u].rc, r, d);
    } else {
      r = u, split(tree[u].lc, val, l, tree[u].lc, d);
    }
    pushup(u);
  }
  int merge(int l, int r) {
    if (!l || !r) {
      return l + r;
    }
    if (tree[l].prm > tree[r].prm) {
      tree[l].rc = merge(tree[l].rc, r), pushup(l);
      return l;
    } else {
      tree[r].lc = merge(l, tree[r].lc), pushup(r);
      return r;
    }
  }
  void newTask(T u, T v) {
    int l = 0, r = 0, p = 0;
    split(root, v + 1, l, p, 0);
    split(l, u, l, r, 1);
    std::cout << tree[r].siz << "\n";
    r = init(u, v);
    root = merge(merge(l, r), p);
  }
  void query() {
    std::cout << tree[root].siz << "\n";
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  FHQTreap t(n);
  while (n--) {
    char opt;
    std::cin >> opt;
    if (opt == 'A') {
      int u, v;
      std::cin >> u >> v;
      t.newTask(u, v);
    } else {
      t.query();
    }
  }

  return 0;
}