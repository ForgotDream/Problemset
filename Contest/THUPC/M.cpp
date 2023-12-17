#include <bits/stdc++.h>

using i64 = long long;

std::string s;
void solve() {
  std::getline(std::cin, s);
  if (s.length() < 19) std::cout << "Human\n";
  else if (s.substr(0, 19) == "You are right, but ") std::cout << "AI\n";
  else std::cout << "Human\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
