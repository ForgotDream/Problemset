/**
 * @file    
 * @author  ForgotDream
<<<<<<< Updated upstream
 * @brief   CDQ
=======
 * @brief   
>>>>>>> Stashed changes
 * @date    2023-07-31
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n, k, p[N], sum;
bool vis[N];
std::vector<int> cir;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;
  k = n - k;
  for (int i = 1; i <= n; i++) std::cin >> p[i];

  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    vis[i] = true;
    int pivot = p[i], cnt = 1;
    while (pivot != i) vis[pivot] = true, pivot = p[pivot], cnt++;
    cir.push_back(cnt), sum += cnt / 2;
  }

  return 0;
}