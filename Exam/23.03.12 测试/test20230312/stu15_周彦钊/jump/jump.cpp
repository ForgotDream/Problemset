#include <bits/stdc++.h>
#include <iostream>
#include <bitset>

using i64 = long long;

std::bitset<(int) 3e4 + 50> b;
std::vector<std::vector<int>> f((int) 5e3 + 50, std::vector<int>((int) 5e3 + 50, -1));

int dfs(int cur, int n, int step) {
  if (cur > n) {
    return 0;
  }
  if (~f[cur][step]) {
    return f[cur][step];
  }
  
  int res = 0;
  
  if (step > 1) {
    res = std::max(res, dfs(cur + step - 1, n, step - 1));
  }
  res = std::max(res, dfs(cur + step, n, step));
  res = std::max(res, dfs(cur + step + 1, n, step + 1));
  
  res += b[cur];
  f[cur][step] = res;
  
  return res;
}

int main() {
  freopen("jump.in", "r", stdin);
  freopen("jump.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  srand(time(0));
  
  int n, d;
  std::cin >> n >> d;
  
  int maxx = 0;
  for (int i = 1; i <= n; i++) {
    int u;
    std::cin >> u;
    maxx = std::max(maxx, u);
    b[u] = true;
  }
  
  if (n > 2000) {
    int ans = 0;
    
    for (int i = 1; i <= 9e8 / n; i++) {
      int pivot = d, step = d, res = 0;
      while (pivot < maxx) {
        res += b[pivot];
        if (step == 1) {
          int delta = rand() % 2;
          step += delta;
          pivot += step;
        } else {
          int delta = rand() % 3 - 1;
          step += delta;
          pivot += step;
        }
      }
      ans = std::max(ans, res);
    }
    
    std::cout << ans << "\n";
    
    return 0;
  }
  
  std::cout << dfs(d, maxx, d) << "\n"; 
  
  return 0;
}
