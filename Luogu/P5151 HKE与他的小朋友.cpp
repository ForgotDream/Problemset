/**
 * @file    P5151 HKE与他的小朋友.cpp
 * @author  ForgotDream
 * @brief   置换
 * @date    2023-03-03
 */
#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  int cnt = 0;
  std::vector<int> cir[n + 1];
  std::vector<int> pos(n + 1), blg(n + 1);
  for (int i = 1; i <= n; i++) {
    if (blg[i]) {
      continue;
    }
    int pivot = i, cur = 0;
    ++cnt;
    do {
      pos[pivot] = cur++;
      blg[pivot] = cnt;
      cir[cnt].push_back(pivot);
      pivot = a[pivot];
    } while (pivot != i);
  }

  std::vector<int> ans(n + 1);
  for (int i = 1; i <= n; i++) {
    auto cur = cir[blg[i]];
    // std::cerr << (pos[i] + k) % cur.size() << "\n";
    ans[cur[(pos[i] + k % cur.size()) % cur.size()]] = i;
  }

  for (int i = 1; i <= n; i++) {
    std::cout << ans[i] << " \n"[i == n];
  }

  return 0;
}