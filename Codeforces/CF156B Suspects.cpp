/**
 * @file    CF156B Suspects.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-09-05
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, a[N], f[N], cnt;
bool sus[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    if (a[i] > 0) f[a[i]]++;
    else f[-a[i]]--, cnt++;
  }
  int tot = 0;
  for (int i = 1; i <= n; i++) {
    if (cnt + f[i] == m) sus[i] = true, tot++;
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] > 0) {
      if (!sus[a[i]]) std::cout << "Lie\n";
      else if (tot == 1) std::cout << "Truth\n";
      else std::cout << "Not defined\n";
    } else {
      if (!sus[-a[i]]) std::cout << "Truth\n";
      else if (tot == 1) std::cout << "Lie\n";
      else std::cout << "Not defined\n";
    }
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}