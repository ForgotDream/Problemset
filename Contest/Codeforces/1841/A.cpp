#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;
  if (n == 2) {
    std::cout << "Bob\n";
  } else if (n == 3) {
    std::cout << "Bob\n";
  } else if (n == 4) {
    std::cout << "Bob\n";
  } else {
    std::cout << "Alice\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}