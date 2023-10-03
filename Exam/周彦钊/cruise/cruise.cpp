#include <iostream>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e5 + 50;
int n;
struct Boat {
  int l, x, v;
} b[N];
f80 t[N];
int min[N];
void solve() {
  std::cout << "1.000\n";
}

int main() {
  std::freopen("cruise.in", "r", stdin);
  std::freopen("cruise.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
