/**
 * @file    CF251B Playing with Permutations.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 105;
int n, k, p[N], q[N], s[N], tmp[N];
bool vis[N];
int l[N], cnt;
void rotate() {
  std::copy(p + 1, p + n + 1, tmp + 1);
  for (int i = 1; i <= n; i++) p[i] = tmp[q[i]];
}
void rev_rotate() {
  std::copy(p + 1, p + n + 1, tmp + 1);
  for (int i = 1; i <= n; i++) p[q[i]] = tmp[i];
}
bool check() {
  for (int i = 1; i <= n; i++) {
    if (p[i] != s[i]) return false;
  }
  return true;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> q[i];
  for (int i = 1; i <= n; i++) std::cin >> s[i];
  if (check()) return std::cout << "NO\n", 0;
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    vis[i] = true;
    int piv = q[i], len = 1;
    while (!vis[piv]) vis[piv] = true, piv = q[piv], len++;
    l[++cnt] = len;
  }
  int lcm = l[1];
  for (int i = 2; i <= cnt; i++) lcm = std::lcm(lcm, l[i]);
  int ans = -1, rev_ans = -1;
  std::iota(p, p + n + 1, 0);
  for (int i = 1; i <= std::min(lcm - 1, k); i++) {
    rotate();
    if (check()) {
      ans = i;
      break;
    }
  }
  std::iota(p, p + n + 1, 0);
  for (int i = 1; i <= std::min(lcm - 1, k); i++) {
    rev_rotate();
    if (check()) {
      rev_ans = i;
      break;
    }
  }
  std::cerr << ans << " " << rev_ans << "\n";
  if (ans != -1) {
    if ((k == 1 || ans != 1 || rev_ans != 1) && (k - ans) % 2 == 0) {
      std::cout << "YES\n";
      return 0;
    }
  }
  if (rev_ans != -1) {
    if ((k == 1 || ans != 1 || rev_ans != 1) && (k - rev_ans) % 2 == 0) {
      std::cout << "YES\n";
      return 0;
    }
  }
  std::cout << "NO\n";
  return 0;
}