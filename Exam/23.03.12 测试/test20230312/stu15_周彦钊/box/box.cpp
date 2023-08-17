#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using i64 = long long;

int main() {
  freopen("box.in", "r", stdin);
  freopen("box.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n;
  std::cin >> n;
  
  std::vector<int> a(n);
  std::vector<bool> vis(n);
  for (auto &i : a) {
    std::cin >> i;
  }
  
  std::sort(a.begin(), a.end());
  
  int ans = 0, rst = n;
  while (rst > 0) {
    std::vector<int> vec;
    ans++;
    
    int pivot = 0, cnt = 0;
    while (pivot < n) {
      if (vis[pivot]) {
        pivot++;
        continue;
      }
      
      cnt++;
      vec.push_back(pivot);
      
      bool flg = false;
      for (int i = pivot + 1; i < n; i++) {
        if (!vis[i] && a[i] >= cnt) {
          pivot = i;
          flg = true;
          break;
        }
      }
      
      if (!flg) {
        break;
      }
    }
    
    for (auto i : vec) {
      vis[i] = true;
      rst--;
    }
  }
  
  std::cout << ans << "\n";
  
  return 0;
}
