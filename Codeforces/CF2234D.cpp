/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>
#include <string>

using i64 = long long;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::string s, t;
  std::cin >> s >> t;

  i64 c1 = 0, c2 = 0, c3 = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') c1++;
    if (t[i] == '1') c2++;
    if (s[i] != t[i]) c3++;
  }

  c1 = c1 * (n - c1), c2 = c2 * (n - c2), c3 = c3 * (n - c3);
  i64 len = (1ll << k) + 1;
  i64 a1, a2, a3;

  if (k % 2) {
    a1 = a2 = a3 = len / 3;
  } else {
    a1 = a2 = (len + 1) / 3;
    a3 = len / 3;
  }

  std::cout << a1 * c1 + a2 * c2 + a3 * c3 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
