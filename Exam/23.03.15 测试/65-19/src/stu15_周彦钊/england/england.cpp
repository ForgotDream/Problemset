#include <bits/stdc++.h>
#include <vector>
#include <stack>
#include <iostream>

using i64 = long long;

int main() {
  freopen("england.in", "r", stdin);
  freopen("england.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
 
  int n;
  std::cin >> n;
  
  std::vector<int> a(n);
  for (auto &i : a) {
    std::cin >> i;
  }
  
  std::stack<int> s;
  std::vector<int> len(n, 0);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] >= a[i]) {
      s.pop();
    }
    if (s.empty()) {
      len[i] = i + 1;
    } else {
      len[i] = i - s.top();
    }
    s.push(i);
  }
  
  while (!s.empty()) {
    s.pop();
  }
  
  for (int i = n - 1; ~i; i--) {
    while (!s.empty() && a[s.top()] >= a[i]) {
      s.pop();
    }
    if (s.empty()) {
      len[i] += (n - 1) - i;
    } else {
      len[i] += s.top() - i;
    }
    s.push(i);
  }
  
  for (int i = 0; i < n; i++) {
    ans = std::max(ans, len[i] * a[i]);
  }
  
  std::cout << ans << "\n";
  
  return 0;
}
