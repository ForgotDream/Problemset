#include <bits/stdc++.h>
#include <iostream>

using i64 = long long;

void solve() {
  i64 a, b;
  std::cin >> a >> b;
  
  i64 ans = 0;
  while (a != b) { 
    // std::cerr << a << " " << b << "\n";
    if (a < b) {
      std::swap(a, b);
    }
    if (a % b == 0) {
      ans += a / b - 1;
      break;
    }
    ans += a / b;
    a -= a / b * b;
  }
  std::cout << ans << "\n";
  
  return;
}

int main() {
  freopen("sword.in", "r", stdin);
  freopen("sword.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int t;
  std::cin >> t;
  
  while (t--) {
    solve();
  }
  
  return 0;
}
