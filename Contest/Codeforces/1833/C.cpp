#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  int odd = 0;
  int minOdd = INT_MAX;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    if (a[i] & 1) {
      odd++;
      minOdd = std::min(minOdd, a[i]);
    }
  }

  bool flg1 = true, flg2 = true;
  for (int i = 0; i < n; i++) {
    if ((a[i] & 1) && (odd == 1 || minOdd >= a[i])) {
      flg1 = false;
    }
    if (!(a[i] & 1) && (odd == 0 || minOdd > a[i])) {
      flg2 = false;
    }
  }

  if (flg1 || flg2) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }

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