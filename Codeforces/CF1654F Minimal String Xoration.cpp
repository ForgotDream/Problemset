/*
 * @file    CF1654F Minimal String Xoration.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-12-22
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50, M = 1;
std::string s;
int n, a[N], p[N], t[N];

void solve() {
  std::cin >> n >> s;
  int mask = 1 << n;
  for (int i = 0; i < mask; i++) a[i] = s[i] - 'a';
  std::iota(p, p + mask, 0);

  for (int i = 1, d = 1; i <= n; i++, d *= 2) {
    auto cmp = [&](int lhs, int rhs) {
      return (a[lhs] < a[rhs]) || (a[lhs] == a[rhs] && a[lhs ^ d] < a[rhs ^ d]);
    };

    std::sort(p, p + mask, cmp);
    int cnt = 0;
    for (int j = 0; j < mask; j++) {
      if (!j || cmp(p[j - 1], p[j])) t[p[j]] = ++cnt;
      else t[p[j]] = cnt;
    }

    std::copy(t, t + mask, a);
  }
  
  int k = p[0];
  for (int i = 0; i < mask; i++) std::cout << s[i ^ k];
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
