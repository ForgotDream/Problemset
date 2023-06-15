/**
 * @file    P3886 神秘的生物.cpp
 * @author  ForgotDream
 * @brief   Plug DP
 * @date    2023-06-15
 */
#include <bits/stdc++.h>

using i64 = long long;

struct hashTable {
  static constexpr int siz = 1e5, mod = 99983;
  std::vector<int> head, nxt;
  std::vector<i64> val, stt;
  int cnt, offset;
  hashTable() {
    cnt = 0;
    head.resize(mod, -1), nxt.resize(siz);
    stt.resize(siz), val.resize(siz);
  }
  void setOffset(int _o) { offset = _o; }
  void clear() { cnt = 0, head.assign(siz, -1); }
  int size() { return cnt; }
  void insert(i64 st, i64 w) {
    int cur = st % mod;
    for (int i = head[cur]; ~i; i = nxt[i]) {
      if (stt[i] == st) {
        val[i] = std::max(val[i], w);
        return;
      }
    }
    stt[cnt] = st, val[cnt] = w;
    nxt[cnt] = head[cur], head[cur] = cnt++;
  }
  void roll() {
    for (int i = 0; i < cnt; i++) { stt[i] <<= offset; }
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector a(n, std::vector<int>(n));
  i64 ans = INT_MIN;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { 
      std::cin >> a[i][j]; 
      ans = std::max(ans, 1ll * a[i][j]); 
    }
  }

  int offset = 3, mask = (1 << offset) - 1;
  auto encode = [&](const std::vector<int> &bit, i64 w) {
    static std::vector<int> b(n + 1);
    b.assign(n + 1, -1), b[0] = 0;
    i64 st = 0;
    int cnt = 1;
    for (int i = n; i >= 0; i--) {
      if (!~b[bit[i]]) { b[bit[i]] = cnt++; }
      st <<= offset, st |= b[bit[i]];
    }
    if (cnt <= 2 && w) { ans = std::max(ans, w); }
    return st;
  };
  auto decode = [&](i64 st) {
    std::vector<int> bit(n + 1);
    for (int i = 0; i <= n; i++) {
      bit[i] = st & mask, st >>= offset;
    }
    return bit;
  };

  std::array<hashTable, 2> h;
  for (int i = 0; i < 2; i++) { h[i].setOffset(offset); }

  int cur = 0, lst = 1;

  auto push = [&](int pl, int dn, int rt, i64 w, const std::vector<int> &bit) {
    auto b = bit;
    b[pl] = dn, b[pl + 1] = rt;
    h[cur].insert(encode(b, w), w);
  };

  h[cur].insert(0, 0);
  for (int i = 0; i < n; i++) {
    h[cur].roll();
    for (int j = 0; j < n; j++) {
      cur ^= 1, lst ^= 1;
      h[cur].clear();
      for (int k = 0; k < h[lst].size(); k++) {
        i64 w = h[lst].val[k];
        auto st = decode(h[lst].stt[k]);
        int lt = st[j], up = st[j + 1];
        if (j == 0) { lt = 0; }
        if (lt && up) {
          int cnt = 0;
          for (int i = 0; i <= n; i++) {
            if (st[i] == up) { cnt++; }
          }
          if (cnt >= 2) { push(j, 0, 0, w, st); }
          for (int l = 0; l <= n; l++) {
            if (st[l] == lt) { st[l] = up; }
          }
          push(j, up, up, w + a[i][j], st);
        } else if (lt && !up) {
          push(j, 0, 0, w, st);
          push(j, lt, lt, w + a[i][j], st);
        } else if (!lt && up) {
          int cnt = 0;
          for (int i = 0; i <= n; i++) {
            if (st[i] == up) { cnt++; }
          }
          if (cnt >= 2) { push(j, 0, 0, w, st); }
          push(j, up, up, w + a[i][j], st);
        } else {
          push(j, 0, 0, w, st);
          push(j, n, n, w + a[i][j], st);
        }
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}