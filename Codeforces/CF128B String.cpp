/**
 * @file    CF128B String.cpp
 * @author  ForgotDream
 * @brief   String
 * @date    2023-08-30
 */
#include <iostream>
#include <queue>
#include <string>

using i64 = long long;

std::string s;
struct shabi {
  int l, r;
  shabi(int _l = 0, int _r = 0) { l = _l, r = _r; }
  bool operator<(const shabi &rhs) const {
    for (int len = 0; len <= r - l; len++) {
      if (rhs.l + len > rhs.r) return true;
      if (s[l + len] != s[rhs.l + len]) return s[l + len] > s[rhs.l + len];
    }
    return false;
  }
};
int n, k;
std::priority_queue<shabi> pq;
void solve() {
  std::cin >> s >> k;
  for (int i = 0; i < s.length(); i++) pq.emplace(i, i);
  for (int i = 1; i < k; i++) {
    auto cur = pq.top();
    pq.pop();
    if (cur.r < s.length() - 1) cur.r++, pq.emplace(cur);
    if (pq.empty()) {
      std::cout << "No such line.\n";
      return;
    }
  }
  std::cout << s.substr(pq.top().l, pq.top().r - pq.top().l + 1) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}