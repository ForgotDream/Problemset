#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> v(n + 1, std::vector<int>(m + 1, 0));
  std::vector<std::vector<int>> f(n + 1, std::vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> v[i][j];
    }
  }
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (v[i][j] == 0) {
        f[i][j] = f[i - 1][j] + 1;
      }
    }
  }
  
  int ans = 0;
  std::vector<int> tmp(m + 1, 0);
  std::stack<int> s1;
  for (int i = 1; i <= n; i++) {
    tmp.clear();
    tmp.resize(m + 1, 0);
    while (!s1.empty()) {
      s1.pop();
    }
    
    for (int j = 1; j <= m; j++) {
      int cur = f[i][j];
      while (!s1.empty() && f[i][s1.top()] >= cur) {
        s1.pop();
      }
      if (s1.empty()) {
        tmp[j] = j;
      } else {
        tmp[j] = j - s1.top();
      }
      s1.push(j);
    }
    
    while (!s1.empty()) {
      s1.pop();
    }
    
    for (int j = m; j >= 1; j--) {
      int cur = f[i][j];
      while (!s1.empty() && f[i][s1.top()] >= cur) {
        s1.pop();
      }
      if (s1.empty()) {
        tmp[j] += m - j;
      } else {
        tmp[j] += s1.top() - j - 1;
      }
      s1.push(j);
    }
    
    for (int j = 1; j <= m; j++) {
      // std::cout << tmp[j] << " \n"[j == m];
      ans = std::max(ans, tmp[j] * f[i][j]);
    }
  }
  
  std::cout << ans << "\n";
  
  return 0;
}
