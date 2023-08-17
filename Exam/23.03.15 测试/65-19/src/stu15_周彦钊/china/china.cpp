#include <bits/stdc++.h>
#include <iostream>

using i64 = long long;

int main() {
  freopen("china.in", "r", stdin);
  freopen("china.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int s, n;
  std::cin >> s >> n;
  
  i64 ans = s;
  for (int i = 1; i <= n; i++) {
    i64 l, r, t;
    std::cin >> l >> r >> t;
    ans += (r - l + 1) * (t - 1);
  }
  
  std::cout << ans << "\n";
  
  return 0;
} 
