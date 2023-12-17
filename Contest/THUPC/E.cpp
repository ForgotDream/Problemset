#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 50;
int n;
i64 a[N], b[N], c[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  for (int i = 1; i <= n; i++) std::cin >> c[i];
  for (int i = 1; i <= n; i++) {
    if (a[i] == 0 && c[i] != 0) {

    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
