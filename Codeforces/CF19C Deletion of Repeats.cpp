/**
 * @file    CF19C Deletion of Repeats.cpp
 * @author  ForgotDream
 * @brief   String + Binary Search
 * @date    2023-08-24
 */
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;

constexpr int N = 1e5 + 50;
constexpr u64 base = 233;
int n, val[N];
struct Hash {
  u64 hash[N], pw[N];
  void init() {
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
      hash[i] = val[i] + base * hash[i - 1];
      pw[i] = base * pw[i - 1];
    }
  }
  u64 operator()(int l, int r) {
    return hash[r] - hash[l - 1] * pw[r - l + 1];
  }
} hash;
int lcp(int l, int r) {
  int lo = 0, hi = r - l, res = 0;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (hash(r - mid + 1, r) == hash(l - mid + 1, l)) lo = mid + 1, res = mid;
    else hi = mid - 1;
  }
  return res;
}
int lcs(int l, int r) {
  int lo = 0, hi = r - l, res = 0;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (hash(l, l + mid - 1) == hash(r, r + mid - 1)) lo = mid + 1, res = mid;
    else hi = mid - 1;
  }
  return res;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> val[i];
  hash.init();
  int p = 1;
  for (int i = 1; i <= n; i++) {
    int l = i + p - 1, r = 2 * i + p - 1;
    if (r > n) break;
    while (r <= n) {
      int lcp = ::lcp(l, r), lcs = ::lcs(l, r);
      if (lcp + lcs > i) p = std::max(p, r - lcp + 1);
      l += i, r += i;
    }
  }
  std::cout << n - p + 1 << "\n";
  for (int i = p; i <= n; i++) std::cout << val[i] << " \n"[i == n];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}