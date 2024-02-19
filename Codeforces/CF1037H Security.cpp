/*
 * @file    CF1037H Security.cpp
 * @author  ForgotDream
 * @brief   SAM + Segment Tree
 * @date    2024-02-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

struct SAM {
  int ch[N][26], len[N], link[N], lst = 1, cnt = 1;

  int expand(int d) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1;
    int p = lst;
    for (; p && !ch[p][d]; p = link[p]) ch[p][d] = cur;
    if (!p) {
      link[cur] = 1;
    } else {
      int q = ch[p][d];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q];
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

struct SegTree {
  struct Node {
    int lc, rc;
  } tree[N << 5];
  int cnt;

  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }

  void modify(int tar, int s, int t, int &u) {
    if (!u) u = ++cnt;
    if (s == t) return;
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
  }

  bool query(int l, int r, int s, int t, int u) {
    if (!u || l > r) return false;
    if (l <= s && t <= r) return true;
    int mid = (s + t) >> 1;
    if (mid >= l && query(l, r, s, mid, lc(u))) return true;
    if (mid < r && query(l, r, mid + 1, t, rc(u))) return true;
    return false;
  }

  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u + v;
    int mid = (s + t) >> 1, p = ++cnt;
    lc(p) = merge(s, mid, lc(u), lc(v));
    rc(p) = merge(mid + 1, t, rc(u), rc(v));
    return p;
  }
} seg;
int rt[N];

std::string s;
int n, q;

std::vector<int> adj[N];

void dfs(int u) {
  for (auto v : adj[u]) {
    dfs(v);
    rt[u] = seg.merge(1, n, rt[u], rt[v]);
  }
}

void solve() {
  std::cin >> s >> q, n = s.length();
  for (int i = 0; i < n; i++) {
    int p = sam.expand(s[i] - 'a');
    seg.modify(i + 1, 1, n, rt[p]);
  }
  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
  dfs(1);

  for (int l, r; q; q--) {
    std::string t;
    char ans = 0;
    std::cin >> l >> r >> t, t += 'a' - 1;
    int m = t.length();
    t = " " + t;

    int p = 1, i, k = 1;
    for (i = 1; i <= m; i++) {
      int d = t[i] - 'a';
      for (int j = d + 1; j < 26; j++) {
        int q = sam.ch[p][j];
        if (q && seg.query(l + i - 1, r, 1, n, rt[q])) {
          ans = j + 'a', k = i;
          break;
        }
      }
      p = sam.ch[p][d];
      if (!p || !seg.query(l + i - 1, r, 1, n, rt[p])) break;
    }

    if (!ans) {
      std::cout << -1 << "\n";
      continue;
    }
    for (int j = 1; j < k; j++) std::cout << t[j];
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
