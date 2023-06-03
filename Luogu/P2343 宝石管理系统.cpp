/**
 * @file    P2343 宝石管理系统.cpp
 * @author  ForgotDream
 * @brief   BST
 * @date    2023-05-29
 */
#include <bits/stdc++.h>

using i64 = long long;

template<typename T = int>
struct FHQTreap {
  std::mt19937 rnd;
  struct Node {
    int lc, rc;
    int siz, prm;
    T val;
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
  void pushup(int u) { 
    tree[u].siz = tree[tree[u].lc].siz + tree[tree[u].rc].siz + 1;
  }
  int init(T val) {
    if (cnt == tree.size() - 1) {
      tree.resize(std::max(1.5 * tree.size(), 10.));
    }
    tree[++cnt].val = val;
    tree[cnt].prm = rnd(), tree[cnt].siz = 1;
    tree[cnt].lc = tree[cnt].rc = 0;
    return cnt;
  }
  void split(int u, T val, int &l, int &r) {
    if (!u) {
      l = r = 0;
      return;
    }
    if (tree[u].val <= val) {
      l = u, split(tree[u].rc, val, tree[u].rc, r);
    } else {
      r = u, split(tree[u].lc, val, l, tree[u].lc);
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
  void insert(T val) {
    int l = 0, r = 0;
    split(root, val, l, r);
    root = merge(merge(l, init(val)), r);
  }
  void erase(T val) {
    int l = 0, r = 0, p = 0;
    split(root, val, l, r);
    split(l, val - 1, l, p);
    p = merge(tree[p].lc, tree[p].rc);
    root = merge(merge(l, p), r);
  }
  int getRankByNum(T val) {
    int l = 0, r = 0, res;
    split(root, val - 1, l, r);
    res = tree[l].siz + 1;
    root = merge(l, r);
    return res;
  }
  int getNumByRank(int u, int rnk) {
    if (rnk == tree[tree[u].lc].siz + 1) {
      return u;
    } else if (rnk > tree[tree[u].lc].siz + 1) {
      return getNumByRank(tree[u].rc, rnk - tree[tree[u].lc].siz - 1);
    } else {
      return getNumByRank(tree[u].lc, rnk);
    }
  }
  T getNumByRank(int rnk) {
    return tree[getNumByRank(root, rnk)].val;
  }
  T getPrecursor(T val) {
    int l = 0, r = 0;
    T res;
    split(root, val, l, r);
    res = tree[getNumByRank(l, tree[l].siz)].val;
    root = merge(l, r);
    return res;
  }
  T getSuccessor(T val) {
    int l = 0, r = 0;
    T res;
    split(root, val - 1, l, r);
    res = tree[getNumByRank(r, 1)].val;
    root = merge(l, r);
    return res;
  }
  T findNearest(T val) {
    T prev = getPrecursor(val), succ = getSuccessor(val);
    if (std::abs(prev - val) <= std::abs(succ - val)) {
      return prev;
    } else {
      return succ;
    }
  }
  bool empty() {
    return tree[root].siz == 0;
  }
  int size() {
    return tree[root].siz;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  FHQTreap<int> t(n);
  for (int i = 0; i < n; i++) {
    int val;
    std::cin >> val;
    t.insert(val);
  }

  while (q--) {
    int opt, val;
    std::cin >> opt >> val;
    if (opt == 1) {
      val = t.size() - val + 1;
      std::cout << t.getNumByRank(val) << "\n";
    } else {
      t.insert(val);
    }
  }

  return 0;
}