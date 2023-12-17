#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50, M = 22;
int n;
std::string s;
std::set<int> pos[N];
void solve() {
  std::cin >> n >> s, s = ' ' + s;
  int d = std::__lg(n);
  std::string cur = s;
  for (int i = 1; i <= d; i++) {
    for (int i = 1; i )
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
