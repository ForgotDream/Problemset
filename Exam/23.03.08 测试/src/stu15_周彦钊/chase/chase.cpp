#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using i64 = long long;

int main() {
  freopen("chase.in", "r", stdin);
  freopen("chase.out", "w", stdout);
  
  int n;
  std::cin >> n;
  
  std::vector<std::pair<int, int>> a(n);
  std::vector<std::pair<i64, int>> st(n);
  int maxx = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
    maxx = std::max(maxx, a[i].first);
  }
  
  for (int i = 0; i < n; i++) {
    st[i].first = i64(maxx - a[i].first) * a[i].second;
    st[i].second = i;
  }
  
  std::sort(st.begin(), st.end());
  
  // std::cerr << std::fixed << std::setprecision(2) << 0.0 << "\n";
  if (n == 2) {
    if (a[st[0].second].second <= a[st[1].second].second) {
      std::cout << std::fixed << std::setprecision(2) << double(st[1].first - st[0].first) << "\n";
    } else {
      std::cout << std::fixed << std::setprecision(2) << .0 << "\n";
    }
    return 0;
  } 
  
  if (a[st[0].second].second < a[st[n - 1].second].second) {
    std::cout << std::fixed << std::setprecision(2) << st[n - 1].first - st[0].first << "\n";
    return 0;
  } 
  
  double minn1 = 1e18, ans = 0, minn2 = 1e18;
  for (int i = 1; i < n; i++) {
    if (a[st[0].second].second <= a[st[i].second].second) {
      continue;
    }
    double x = double(st[i].first - st[0].first) / (a[st[0].second].second - a[st[i].second].second);
    minn1 = std::min(minn1, x);
  }
  for (int i = 0; i < n - 1; i++) {
    if (a[st[n - 1].second].second >= a[st[i].second].second) {
      continue;
    }
    double x = double(st[n - 1].first - st[i].first) / (a[st[i].second].second - a[st[n - 1].second].second);
    minn2 = std::min(minn2, x);
  }
  
  std::cerr << minn1 << " " << minn2 << '\n';
  
  ans = std::min(a[st[n - 1].second].second * minn1 + st[n - 1].first - a[st[0].second].second * minn1 - st[0].first,
                 a[st[n - 1].second].second * minn2 + st[n - 1].first - a[st[0].second].second * minn2 - st[0].first);
  
  std::cout << std::fixed << std::setprecision(2) << ans << "\n";
  
  return 0;
}


  /* else if (n == 3) {
    if (a[st[0].second].second <= a[st[2].second].second) {
      std::cout << std::fixed << std::setprecision(2) << double(st[2].first - st[0].first) << "\n";
    } else {
      if (a[st[0].second].second <= a[st[1].second].second) {
        double x = double(st[2].first - st[1].first) / (a[st[1].second].second - a[st[2].second].second);
        x = st[2].second + x * a[st[2].second].second - st[0].second - x * a[st[0].second].second;
        std::cout << std::fixed << std::setprecision(2) << x << "\n";
      } else if (a[st[1].second].second <= a[st[2].second].second) {
        double x = double(st[1].first - st[0].first) / (a[st[0].second].second - a[st[1].second].second);
        x = st[2].second + x * a[st[2].second].second - st[0].second - x * a[st[0].second].second;
        std::cout << std::fixed << std::setprecision(2) << x << "\n";
      } else {
        
      }
    }
    return 0;
  }
  */
