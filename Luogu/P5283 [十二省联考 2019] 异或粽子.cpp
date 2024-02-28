/*
 * @file    P5283 [十二省联考 2019] 异或粽子.cpp
 * @author  ForgotDream
 * @brief   01 Trie + Heap
 * @date    2024-02-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5e5 + 50, W = 32;

int n, k;
u32 a[N];

struct Trie {
  int ch[N * W][2], siz[N * W], cnt;

  void insert(u32 val) {
    int p = 0;
    for (int i = 31; ~i; i--) {
      int d = val >> i & 1;
      if (!ch[p][d]) ch[p][d] = ++cnt;
      p = ch[p][d], siz[p]++;
    }
  }

  u32 query(u32 val, int rnk) {
    int p = 0;
    u32 res = 0;
    for (int i = 31; ~i; i--) {
      int d = val >> i & 1;
      if (!ch[p][d ^ 1]) p = ch[p][d];
      else if (rnk <= siz[ch[p][d ^ 1]]) p = ch[p][d ^ 1], res += 1 << i;
      else rnk -= siz[ch[p][d ^ 1]], p = ch[p][d];
    }
    return res;
  }
} trie;

struct Node {
  int u, p;
  u32 val;
  Node() = default;
  Node(int _u, int _p, u32 _v) : u(_u), p(_p), val(_v) {}
  friend bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.val < rhs.val;
  }
};

void solve() {
  std::cin >> n >> k, k <<= 1;
  for (int i = 1; i <= n; i++) std::cin >> a[i], a[i] ^= a[i - 1];
  for (int i = 0; i <= n; i++) trie.insert(a[i]);

  std::priority_queue<Node> pq;
  for (int i = 0; i <= n; i++) pq.emplace(i, 1, trie.query(a[i], 1));

  i64 ans = 0;
  for (int i = 1; i <= k; i++) {
    Node u = pq.top();
    ans += u.val, pq.pop();
    if (u.p < n) pq.emplace(u.u, u.p + 1, trie.query(a[u.u], u.p + 1));
  }
  std::cout << (ans >> 1) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
