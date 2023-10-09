/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-09
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k ,q;
int l[N], a[N], b[N];
std::stack<int, std::vector<int>> s;
int f[20][N], g[20][N];
void solve() {
  std::cin >> n >> k >> q;
  for (int i = 1; i <= n; i++) std::cin >> l[i];
  s.push(1);
  for (int i = 1; i <= n; i++) {
    while (!s.empty() && a[st.top()] < a[i]) st.pop(); 
    f[0][i] = s.top(), s.push(i);
  }
  while (!s.empty()) s.pop();
  s.push(b);
  for (int i = n; i >= 1; i--) {
    while (!s.empty() && a[st.top()] < a[i]) st.pop();
    g[0][i] = s.top(), s.push(i);
  }
  for (int i = 1; i <= 20; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = std::max(f[j][f[i - 1][j]], f[i - 1][g[i - 1][j]]);
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
