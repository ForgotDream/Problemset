/**
 * @file    CF27C Unordered Subsequence.cpp
 * @author  ForgotDream
 * @brief   单调栈
 * @date    2023-08-23
 */
#include <algorithm>
#include <iostream>
#include <stack>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, a[N], gt[N], lt[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  std::fill(lt + 1, lt + n + 1, n + 1);
  std::fill(gt + 1, gt + n + 1, n + 1);
  std::stack<int> s;
  for (int i = n; i >= 1; --i) {
    while (!s.empty() && a[s.top()] >= a[i]) s.pop();
    if (!s.empty()) lt[i] = s.top();
    s.push(i);
  }
  while (!s.empty()) s.pop();
  for (int i = n; i >= 1; --i) {
    while (!s.empty() && a[s.top()] <= a[i]) s.pop();
    if (!s.empty()) gt[i] = s.top();
    s.push(i);
  }
  for (int i = 1; i <= n - 2; i++) {
    if (lt[i] != n + 1 && gt[lt[i]] != n + 1) {
      std::cout << 3 << "\n";
      std::cout << i << " " << lt[i] << " " << gt[lt[i]] << "\n";
      return;
    }
    if (gt[i] != n + 1 && lt[gt[i]] != n + 1) {
      std::cout << 3 << "\n";
      std::cout << i << " " << gt[i] << " " << lt[gt[i]] << "\n";
      return;
    }
  }
  std::cout << 0 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}