#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int q;
  std::cin >> q;
  std::vector<int> a(q);
  int pivot = 0, lst = 0;
  for (int i = 0; i < q; i++) {
    std::cin >> a[i];
    if (i == 0) {
      std::cout << 1, lst = a[i];
    } else {
      if (pivot) {
        if (a[i] <= a[0] && a[i] >= lst) {
          lst = a[i], std::cout << 1;
        } else {
          std::cout << 0;
        }
      } else {
        if (a[i] >= lst) {
          lst = a[i], std::cout << 1;
        } else {
          if (a[i] <= a[0]) {
            pivot = i, lst = a[i], std::cout << 1;
          } else {
            std::cout << 0;
          }
        }
      }
    }
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}