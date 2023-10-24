#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::string s;
  std::cin >> n >> s;

  if (std::count(s.begin(), s.end(), 'o') >= 1 && std::count(s.begin(), s.end(), 'x') == 0) {
    std::cout << "Yes" << "\n";
  } else {
    std::cout << "No" << "\n";
  }

  return 0;
}