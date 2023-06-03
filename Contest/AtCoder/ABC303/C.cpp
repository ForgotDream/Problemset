#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, h, k;
  std::cin >> n >> m >> h >> k;

  std::string s;
  std::cin >> s;

  std::set<std::pair<int, int>> st;
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    st.emplace(x, y);
  }

  int curx = 0, cury = 0;
  for (int i = 0; i < n; i++) {
    std::cerr << curx << " " << cury << "\n";
    if (s[i] == 'R') {
      curx += 1;
    } else if (s[i] == 'L') {
      curx -= 1;
    } else if (s[i] == 'U') {
      cury += 1;
    } else {
      cury -= 1;
    }
    h--;
    if (h < 0) {
      std::cout << "No\n";
      return 0;
    }
    if (st.count(std::make_pair(curx, cury)) && h < k) {
      h = k;
      st.erase(std::make_pair(curx, cury));
    }
  }

  if (h < 0) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
  }

  return 0;
}