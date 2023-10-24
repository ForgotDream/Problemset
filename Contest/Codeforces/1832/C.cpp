#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> b;
  b.push_back(a[0]);

  for (int i = 1; i < n; i++) {
    if (a[i] != a[i - 1]) {
      b.push_back(a[i]);
    }
  }

  n = b.size();

  if (n <= 2) {
    std::cout << n << "\n";
    return;
  }


  int cnt = 2;
  for (int i = 1; i < n - 1; i++) {
    if (b[i] > b[i - 1] && b[i] > b[i + 1]) {
      cnt++;
    } else if (b[i] < b[i - 1] && b[i] < b[i + 1]) {
      cnt++;
    }
  }

  std::cout << cnt << "\n";

  return;
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