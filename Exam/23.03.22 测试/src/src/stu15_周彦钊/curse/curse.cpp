#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <iostream>

using i64 = long long;

int main() {
  freopen("curse.in", "r", stdin);
  freopen("curse.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n;
  std::cin >> n;
  
  std::string s;
  std::cin >> s;
  int l = s.length();
  
  std::vector<std::vector<int>> a(l, std::vector<int>(n));
  for (int i = 0; i < l; i++) {
    a[i][0] = (s[i] == '1');
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < l; j++) {
      char c;
      std::cin >> c;
      a[j][i] = (c == '1');
    }
  }
  
  for (int i = 0; i < l; i++) {
    int cnt = std::count(a[i].begin(), a[i].end(), 1);
    if (cnt > n - cnt) {
      std::cout << "1";
    } else {
      std::cout << "0";
    }
  }
  std::cout << "\n";
  
  return 0;
}
