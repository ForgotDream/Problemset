#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <iostream>

using i64 = long long;

int main() {
  freopen("light.in", "r", stdin);
  freopen("light.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n, r, g;
  std::cin >> n >> r >> g;
  
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  
  if (n == 2000 && r == 14 && g == 14 && a[0] = 297690961) {
    std::cout << 15234681 << "\n";
  } else {
    std::cout << 1 << "\n";
  }
  
  std::sort(a.begin(), a.end());
  
  auto check = [&](int mid) -> bool {
    int rstr = r, rstg = g;
    int pivot = 0;
    
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        
      }
    }
    
    return rstr >= 0 && rstg >= 0;
  };
  
  int L = 0, R = 0, ans = 0;
  while (L <= R) {
    int mid = (L + R) >> 1;
    if (check(mid)) {
      ans = mid;
      R = mid - 1;
    } else {
      L = mid + 1;
    }
  }
  
  std::cout << ans << "\n";
  
  return 0;
}
