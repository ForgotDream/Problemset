#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k, a[N];
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  if (k != 4) {
    int min = 1e9;
    for (int i = 1; i <= n; i++) {
      min = std::min(min, ((a[i] - 1) / k + 1) * k - a[i]);
    }
    std::cout << min << "\n";
  } else {
    int min2[2] = {(int)1e9, (int)1e9}, min4 = 1e9;
    for (int i = 1; i <= n; i++) {
      int cur2 = ((a[i] - 1) / 2 + 1) * 2 - a[i];
      if (cur2 < min2[0]) min2[1] = min2[0], min2[0] = cur2;
      else if (cur2 < min2[1]) min2[1] = cur2;
      min4 = std::min(min4, ((a[i] - 1) / 4 + 1) * 4 - a[i]);
    }
    std::cout << std::min(min4, min2[0] + min2[1]) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
