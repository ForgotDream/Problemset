/**
 * @file    CF814B An express train to reveries.cpp
 * @author  ForgotDream
 * @brief   Simulation
 * @date    2023-09-05
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 2050;
int n, a[N], b[N], ans[N];
int pos[3];
bool used[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] != b[i]) pos[++cnt] = i;
  }
  for (int i = 1; i <= n; i++) {
    if (i == pos[1] || i == pos[2]) continue;
    used[a[i]] = true, ans[i] = a[i];
  }
  if (cnt == 1) {
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        ans[pos[1]] = i;
        break;
      }
    }
  } else {
    if (!used[a[pos[1]]] && !used[b[pos[2]]]) {
      ans[pos[1]] = a[pos[1]], ans[pos[2]] = b[pos[2]];
    } else {
      ans[pos[1]] = b[pos[1]], ans[pos[2]] = a[pos[2]];
    }
  }
  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}