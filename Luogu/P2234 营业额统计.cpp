/**
 * @file    P2234 营业额统计.cpp
 * @author  ForgotDream
 * @brief   BST
 * @date    2023-05-29
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace FastIO{
    char buf[1 << 23], *p1 = buf, *p2 = buf;
    inline char gc() {
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
    }

    template<typename T>
    inline void read(T& x) {
        x = 0;
        T f = 1;
        char c = gc();
        while (!isdigit(c)) {
            if (c == '-') f = -1;
            c = gc();
        }
        while (isdigit(c)) x = x * 10 + c - '0', c = gc();
        x *= f;
        return;
    }

    template<typename T, typename ... args>
    inline void read(T& x, args& ... tmp) {
        read(x);
        read(tmp...);
        return;
    }

    template<typename T>
    inline void print(T x) {
        if (x < 0) putchar('-'), x = -x;
        if (x / 10) print(x / 10);
        putchar(x % 10 + '0');
        return;
    }

    template<typename T>
    inline void print(T x, char c) {
        print(x), putchar(c);
        return;
    }
}
using namespace FastIO;

struct FHQTreap {
  std::mt19937 rnd;
  struct Node {
    int lc, rc;
    int siz, prm, val;
  };
  std::vector<Node> tree;
  int cnt, root;

  FHQTreap(int _n) {
    rnd = std::mt19937(
      std::chrono::system_clock::now().time_since_epoch().count()
    );
    tree.resize(_n);
    cnt = 0, root = 0;
  };

  void pushup(int u) {
    tree[u].siz = tree[tree[u].lc].siz + tree[tree[u].rc].siz + 1;
  }

  int init(int val) {
    if (cnt == tree.size() - 1) {
      tree.resize(std::max(1.5 * tree.size(), 10.));
    }
    tree[++cnt].val = val;
    tree[cnt].prm = rnd(), tree[cnt].siz = 1;
    tree[cnt].lc = tree[cnt].rc = 0;
    return cnt;
  }

  void split(int u, int val, int &l, int &r) {
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

  void insert(int val) {
    int l = 0, r = 0;
    split(root, val, l, r);
    root = merge(merge(l, init(val)), r);
  }

  void erase(int val) {
    int l = 0, r = 0, p = 0;
    split(root, val, l, r);
    split(l, val - 1, l, p);
    p = merge(tree[p].lc, tree[p].rc);
    root = merge(merge(l, p), r);
  }

  int getRankByNum(int val) {
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

  int getNumByRank(int rnk) {
    return tree[getNumByRank(root, rnk)].val;
  }

  int getPrecursor(int val) {
    int l = 0, r = 0, res;
    split(root, val, l, r);
    res = tree[getNumByRank(l, tree[l].siz)].val;
    root = merge(l, r);
    return res;
  }

  int getSuccessor(int val) {
    int l = 0, r = 0, res;
    split(root, val - 1, l, r);
    res = tree[getNumByRank(r, 1)].val;
    root = merge(l, r);
    return res;
  }
};

signed main() {
  int n;
  read(n);

  FHQTreap t(n);
  t.insert(INT_MAX), t.insert(INT_MIN);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int u;
    read(u);
    if (i == 0) {
      ans += u;
      t.insert(u);
      continue;
    }
    int prev = t.getPrecursor(u), succ = t.getSuccessor(u);
    t.insert(u);
    // std::cerr << prev << " " << succ << "\n";
    ans += std::min(std::abs(1ll * prev - u), std::abs(1ll * succ - u));
  }

  print(ans, '\n');

  return 0;
}