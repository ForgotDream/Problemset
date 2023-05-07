/**
 * @file    AT_agc023_f 01 on Tree.cpp
 * @author  ForgotDream
 * @brief   DSU + Heap
 * @date    2023-05-07
 */
#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
  int n;
  std::vector<int> fa, siz;

  DSU(int _n) : n(_n) {
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    siz.resize(n, 1);
    return;
  }

  int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  }

};

struct Node {
  int cnt0, cnt1, idx;
  Node(int _c0 = 0, int _c1 = 0, int _idx = 0) 
    : cnt0(_c0), cnt1(_c1), idx(_idx) {}
};

bool operator<(const Node &lhs, const Node &rhs) {
  return (i64) lhs.cnt0 * rhs.cnt1 < (i64) lhs.cnt1 * rhs.cnt0;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> frm(n + 1);
  for (int i = 0; i  < n - 1; i++) {
    std::cin >> frm[i + 2];
  }

  std::vector cnt(n + 1, std::vector<int>(2));
  for (int i = 0; i < n; i++) {
    int c;
    std::cin >> c;
    cnt[i + 1][c]++;
  }
  
  std::priority_queue<Node> pq;
  for (int i = 2; i <= n; i++) {
    pq.emplace(cnt[i][0], cnt[i][1], i);
  }

  DSU dsu(n + 1);
  i64 ans = 0;
  while (!pq.empty()) {
    Node u = pq.top();
    pq.pop();
    int fau = dsu.find(u.idx), cnt0 = u.cnt0, cnt1 = u.cnt1;

    if (cnt[fau][0] != cnt0 || cnt[fau][1] != cnt1) {
      continue;
    }

    int fav = dsu.find(frm[fau]);
    ans += (i64) cnt[fav][1] * cnt[fau][0];
    cnt[fav][0] += cnt[fau][0];
    cnt[fav][1] += cnt[fau][1];
    dsu.fa[fau] = fav;

    if (fav > 1) {
      pq.emplace(cnt[fav][0], cnt[fav][1], fav);
    }
  }

  std::cout << ans << "\n";

  return 0;
}