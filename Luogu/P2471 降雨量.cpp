/**
 * @file    P2471 降雨量.cpp
 * @author  ForgotDream
 * @brief   FHQ
 * @date    2023-03-25
 */
#include <bits/stdc++.h>

namespace FastIO{
  static char buf[1 << 23], *p1 = buf, *p2 = buf;
  inline char gc() {
    if (p1 == p2) {
      p2 = (p1 = buf) + std::fread(buf, 1, 1 << 23, stdin);
    }
    return *p1++;
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

using i64 = long long;
using f80 = long double;
using namespace FastIO;

std::mt19937 rnd = std::mt19937(std::time(nullptr));
struct FHQTreap {
  int root;
  // static std::mt19937 rnd;
  struct Node {
    int y, r, prm, lc, rc, max, size;
    Node(int y, int r) : y(y), r(r), prm(rnd()), lc(0), rc(0), max(r), size(1) {}
  };
  std::vector<Node> node;

  FHQTreap() {
    // rnd = std::mt19937(std::time(nullptr));
    root = init(0, 0);
    // std::cerr << root << "\n";
    return;
  }

  int init(int y, int r) {
    node.emplace_back(y, r);
    return node.size() - 1;
  }

  void update(Node &u) {
    u.max = u.r;
    u.max = std::max(u.max, node[u.lc].max);
    u.max = std::max(u.max, node[u.rc].max);
    u.size = (u.lc ? node[u.lc].size : 0) + (u.rc ? node[u.rc].size : 0) + 1;
    return;
  }

  void split(int u, int x, int &l, int &r) {
    if (!u) {
      l = r = 0;
      return;
    }
    if (node[u].y < x) {
      l = u;
      split(node[u].rc, x, node[u].rc, r);
    } else {
      r = u;
      split(node[u].lc, x, l, node[u].lc);
    }
    update(node[u]);
    return;
  }

  int merge(int l, int r) {
    if (!l || !r) {
      return l + r;
    }
    if (node[l].prm < node[r].prm) {
      node[l].rc = merge(node[l].rc, r);
      update(node[l]);
      return l;
    } else {
      node[r].lc = merge(l, node[r].lc);
      update(node[r]);
      return r;
    }
  }
};

void query(int l, int r, FHQTreap &fhq) {
  if (l >= r) {
    std::cout << "false" << "\n";
    return;
  }

  int piv1, piv2, piv3, piv4, piv5;
  fhq.split(fhq.root, l, piv1, piv2);
  fhq.split(piv2, l + 1, piv2, piv3);
  fhq.split(piv3, r, piv3, piv4);
  fhq.split(piv4, r + 1, piv4, piv5);

  auto merge = [&]() -> void {
    fhq.root = fhq.merge(fhq.merge(piv1, piv2), fhq.merge(fhq.merge(piv3, piv4), piv5));
    return;
  };

  if (piv2 && piv4) {
    if (fhq.node[piv2].r < fhq.node[piv4].r) {
      puts("false");
    } else if (piv3 && fhq.node[piv3].max >= fhq.node[piv4].r) {
      puts("false");
    } else if (piv3 && fhq.node[piv3].size < r - l - 1) {
      puts("maybe");
    } else if (!piv3 && r - l - 1 > 0) {
      puts("maybe");
    } else {
      puts("true");
    }
  } else if (!piv2 && piv4) {
    if (piv3 && fhq.node[piv3].max >= fhq.node[piv4].r) {
      puts("false");
    } else {
      puts("maybe");
    }
  } else if (piv2 && !piv4) {
    if (piv3 && fhq.node[piv3].max >= fhq.node[piv2].r) {
      puts("false");
    } else {
      puts("maybe");
    }
  } else {
    puts("maybe");
  }

  merge();
  return;
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  static const int INF = 0x3f3f3f3f;

  int n;
  read(n);
  FHQTreap fhq;
  for (int i = 0; i < n; i++) {
    int y, r;
    read(y, r);
    fhq.root = fhq.merge(fhq.root, fhq.init(y, r));
  }

  int m;
  read(m);
  for (int i = 0; i < m; i++) {
    int l, r;
    read(l, r);
    query(l, r, fhq);
  }

  return 0;
}