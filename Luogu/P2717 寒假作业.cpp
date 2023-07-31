/**
 * @file    P2717 寒假作业.cpp
 * @author  ForgotDream
 * @brief   CDQ
 * @date    2023-07-31
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k, a[N], s[N];
i64 ans;

void solve(int l, int r) {
  if (l == r) {
    if (a[l] >= 0) ans++;
    return;
  }
  int mid = (l + r) >> 1;
  solve(l, mid), solve(mid + 1, r);

  std::vector<int> lv, rv;
  for (int i = l; i <= mid; i++) lv.push_back(s[mid] - s[i - 1]);
  for (int i = mid + 1; i <= r; i++) rv.push_back(s[i] - s[mid]);
  std::sort(lv.begin(), lv.end());
  std::sort(rv.begin(), rv.end(), std::greater<int>());

  int i = 0, j = 0;
  while (i < lv.size()) {
    while (j < rv.size() && lv[i] + rv[j] >= 0) j++;
    i++, ans += j;
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);  

  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) 
    std::cin >> a[i], a[i] -= k, s[i] = a[i] + s[i - 1];
  solve(1, n);
  std::cout << ans << "\n";

  return 0;
}
