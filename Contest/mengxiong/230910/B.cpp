/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-09-10
 */
#include <algorithm>
#include <iostream>
#include <vector> 
#include <numeric>

using i64 = long long;

i64 n, b, ans, cnt;
namespace B_LESS_THAN_6 {
int a[15], tot;
void dfs(int u, int cnt, int lim) {
  if (cnt == lim + 1) {
    do {
      i64 cur = 0;
      for (int i = 1; i <= lim; i++) cur = cur * b + a[i];
      if (cur % n == 0) {
        tot++;
        if (tot == 2) {
          std::cout << cur << "\n";
          exit(0);
        }
      }  
    } while (std::prev_permutation(a + 1, a + lim + 1));
    return;
  }
  for (int i = u - 1; i >= 0; i--) {
    a[cnt] = i;
    dfs(i, cnt + 1, lim);
  }
}
void solve() {
  for (int i = b; i >= 1; i--) {
    dfs(b, 1, i);
  }
  if (cnt == 1) {
    std::cout << 0 << '\n';
    return;
  }
  std::cout << -1 << "\n";
}
}  // namespace B_LESS_THAN_6
namespace N_GREATER_THAN_1E5 {
bool check(i64 num) {
  int cnt[15] = {0};
  while (num) {
    cnt[num % b]++;
    if (cnt[num % b] > 1) return false;
    num /= b;
  }
  return true;
}
void solve() {
  i64 cnt = 0, lim = 0;
  for (int i = b - 1; ~i; i--) lim = lim * b + i;
  if (n > lim) {
    std::cout << -1 << "\n";
    return;
  }
  for (int i = lim / n; i >= 0; i--) {
    i64 cur = i * n;
    if (check(cur)) cnt++;
    if (cnt == 2) {
      std::cout << cur << "\n";
      return;
    }
  }
  std::cout << -1 << "\n";
}
}  // namespace N_GREATER_THAN_1E5
void solve() {
  std::cin >> n >> b;
  if (b <= 6) {
    B_LESS_THAN_6::solve();
  } else if (n >= 1e5) {
    N_GREATER_THAN_1E5::solve();
  }
}

signed main() {
  std::freopen("multi.in", "r", stdin);
  std::freopen("multi.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}