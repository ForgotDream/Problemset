#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::string s, t;
  std::cin >> n >> s >> t;

  auto check = [&](int i) {
    bool flg = false;
    flg |= (s[i] == t[i]) 
        || (s[i] == '1' && t[i] == 'l') 
        || (s[i] == '0' && t[i] == 'o');
    flg |= (s[i] == 'l' && t[i] == '1') 
        || (s[i] == 'o' && t[i] == '0');
    return flg;
  };

  for (int i = 0; i < n; i++) {
    if (!check(i)) {
      std::cout << "No\n";
      return 0;
    }
  }

  std::cout << "Yes\n";

  return 0;
}