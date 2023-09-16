/**
 * @file    CF37B Computer Game.cpp
 * @author  ForgotDream
 * @brief   Simulation
 * @date    2023-09-04
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using i64 = long long;
using pll = std::pair<i64, i64>;

const int N = 1e3 + 5;
i64 n, m, maxHP, reg, sum;
struct Node {
  i64 del, dmg;
} a[N];
bool used[N];
std::vector<pll> ans;
void solve() {
  std::cin >> n >> maxHP >> reg;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].del >> a[i].dmg;
    if (a[i].del == 100) sum += a[i].dmg;
  }
  if (sum <= reg) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
  i64 HP = maxHP, cnt = 0;
  sum = 0;
  while (HP > 0) {
    HP = std::min(HP - sum + reg, maxHP);
    if (HP <= 0) break;
    int max = 0, pos = 0;
    bool flag = false;
    for (int i = 1; i <= n; i++) {
      if (!used[i] && HP * 100 <= a[i].del * maxHP && a[i].dmg > max) {
        max = a[i].dmg;
        flag = true;
        pos = i;
      }
    }
    if (flag) {
      sum += max;
      used[pos] = true;
      ans.push_back(pll(pos, cnt));
    }
    cnt++;
  }
  std::cout << cnt << " " << ans.size() << "\n";
  for (auto [x, y] : ans) std::cout << y << " " << x << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}