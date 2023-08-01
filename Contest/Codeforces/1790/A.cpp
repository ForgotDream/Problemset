#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string pi = "314159265358979323846264338327";
  std::string s;
  std::cin >> s;
  int p = 0;
  while (p < s.size() && s[p] == pi[p]) p++;
  std::cout << p << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}