#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::string s;

  std::cin >> n >> s;

  int ans = -1, cnt = 0;
  bool fir = false;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == 'o') {
      if (cnt == 0 && i != 0) {
        fir = true;
      }
      cnt++;
    } else if (s[i] == '-') {
      if (cnt) {
        ans = std::max(ans, cnt);
        cnt = 0;
        fir = false;
      }
    }
  }

  if (cnt && fir) {
    ans = std::max(ans, cnt);
  }

  std::cout << ans << "\n";

  return 0;
}