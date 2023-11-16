/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-11-16
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 5e5 + 50;
int n;
ti3 a1[N], a2[N];
bool vis[N];
std::vector<int> b1, b2;
int find1(int u) {
  return std::lower_bound(b1.begin(), b1.end(), u) - b1.begin() + 1;
}
void solve() {
  std::cin >> n >> m1 >> m2;
  for (int i = 1; i <= m1; i++) {
    auto &[l, r, idx] = a1[i];
    std::cin >> l >> r, idx = i;
    b1.push_back(l), b1.push_back(r);
  }
  for (int i = 1; i <= m2; i++) {
    auto &[l, r, idx] = a2[i];
    std::cin >> l >> r, idx = i;
    b2.push_back(l), b2.push_back(r);
  }
  std::sort(b1.b1egin(), b1.end());
  b1.erase(std::unique(b1.b1egin(), b1.end()));
  std::sort(b2.b2egin(), b2.end());
  b2.erase(std::unique(b2.b2egin(), b2.end()));
  for (int i = 1; i <= m1; i++) {
    auto &[l, r, idx] = m1[i];
  }
  for (int i = 0; i <= n; i++) {
    int rst1 = i, rst2 = n - i, cnt = 0;
    for (int i = 1; i <= m1; i++) {
      if (rst1) rst1--, cnt++;
      
    }
    for (int i = 1; i <= m2; i++) {

    }
    ans = std::max(ans, cnt);
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
