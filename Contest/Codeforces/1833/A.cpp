#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::string s;
  std::cin >> n >> s;

  std::set<std::string> st;
  for (int i = 0; i < n - 1; i++) {
    st.insert(s.substr(i, 2));
  }

  std::cout << st.size() << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}