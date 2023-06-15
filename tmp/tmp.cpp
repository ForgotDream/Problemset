/**
 * @file    
 * @author  ForgotDream
 * @brief   
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

  return 0;
}