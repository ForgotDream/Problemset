/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>
#include <string>
#include <vector>

using i64 = long long;

constexpr int inf = 2e9;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::string s;
  std::cin >> s;

  if (k >= n) {
    std::cout << std::string(n, '1') << "\n";
    return;
  }

  std::vector<int> pre(n + 1, 0), suf(n + 1, 0);
  for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + (s[i] == '(');
  for (int i = n - 1; ~i; i--) suf[i] = suf[i + 1] + (s[i] == ')');

  int x = 0, xx = inf;
  for (int i = 0; i <= k; i++) {
    int cur = inf;
    for (int j = 0; j <= n; j++) {
      cur = std::min(cur, std::max(0, pre[j] - i) + std::max(0, suf[j] - (k - i)));
    }
    if (cur < xx) x = i, xx = cur;
  }

  std::cerr << x << "\n";

  int dx = 0, dy = 0;
  std::string ans(n, '0');

  for (int i = 0; i < n && dx < x; i++) if (s[i] == '(') ans[i] = '1', dx++;
  for (int i = n - 1; ~i && dy < k - x; i--) if (s[i] == ')') ans[i] = '1', dy++;

  std::cout << ans << "\n";
}


// f[i][j] -> min remove for length j
// f[i][j] = min(f[i][j + 2] + 1, f[i - 1])

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
