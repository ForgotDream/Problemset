#include <bits/stdc++.h>

using i64 = long long;

bool isPrime(int n) {
  if (n <= 2) {
    return n == 2;
  }
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

void solve() {
  int n, m;
  std::cin >> n >> m;
  
  if (m == 1 || n == 1) {
    std::cout << "YES\n";
    return;
  } else if (n % m == 0) {
    std::cout << "NO\n";
    return;
  } else if (n < m) {
    std::cout << "NO\n";
    return;
  } else if (isPrime(n)) {
    std::cout << "YES\n";
    return;
  }

  for (int i = 2; i <= m; i++) {
    if (n % i == 0) {
      std::cout << "NO\n";
      return;
    }
  }

  std::cout << "YES\n";

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