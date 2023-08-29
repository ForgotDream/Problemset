#include <iostream>
#include <set>

using i64 = long long;

int m;
void solve() {
  std::cin >> m;
  std::set<int> s;
  for (int i = 1; i <= m; i++) {
    if (1ll * i * i * i <= m) s.insert(i * i * i);
    else break;
  }
  for (int i = 1; i <= m; i++) {
    if (1ll * i * i <= m) s.insert(i * i);
    else break;
  }
  std::cout << s.size() << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}