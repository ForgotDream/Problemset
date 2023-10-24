#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::string s;

  std::cin >> n >> s;
  
  int cnt = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '*') {
      if (cnt & 1) {
        std::cout << "in" << "\n";
      } else {
        std::cout << "out" << "\n";
      }
      return 0;
    } else if (s[i] == '|') {
      cnt++;
    }
  }

  return 0;
}