/**
 * @file    P2421 [NOI2002] 荒岛野人.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 16;
int n, s[N], p[N], l[N];
int exgcd(int a, int b, int &x, int &y) {
  if (!b) return x = 1, y = 0, a;
  int d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}
bool check(int u) {
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      int a = p[i] - p[j], b = u, c = s[j] - s[i], x, y;
      auto d = exgcd(a, b, x, y);
      if (c % d) continue;
      a /= d, b /= d, c /= d;
      if (b < 0) b = -b;
      x = (x * c % b + b) % b;
      if (x <= l[i] && x <= l[j]) return false;
    }
  }
  return true;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> s[i] >> p[i] >> l[i];
  int base = *std::max_element(s + 1, s + n + 1);
  for (int i = base;; i++) if (check(i)) return std::cout << i << "\n", void();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
