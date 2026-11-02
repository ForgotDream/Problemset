#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s;
  std::cin >> s;

  if (s.length() != 8) {
    std::cout << "Well-Being\n";
    return;
  }

  std::set<char> a = {'a', 'e', 'i', 'o', 'u'};
  for (int i = 0; i < 8; i += 2) {
    if (a.count(s[i])) {
      std::cout << "Well-Being\n";
      return;
    }
  }
  for (int i = 1; i < 8; i += 2) {
    if (!a.count(s[i])) {
      std::cout << "Well-Being\n";
      return;
    }
  }

  std::cout << "Suspected Virus\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
