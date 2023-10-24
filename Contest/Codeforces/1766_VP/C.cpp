#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n;
bool a[3][N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c == 'B');
    }
  }
  for (int i = 2; i < n; i++) {
    if (a[1][i] && !a[1][i - 1] && !a[1][i + 1]) {
      std::cout << "NO\n";
      return;
    }
    if (a[2][i] && !a[2][i - 1] && !a[2][i + 1]) {
      std::cout << "NO\n";
      return;
    }
  }
  for (int i = 2; i <= n; i++) {
    if (a[1][i] && !a[1][i - 1] && !a[2][i]) {
      std::cout << "NO\n";
      return;
    }
    if (a[2][i] && !a[2][i - 1] && !a[1][i]) {
      std::cout << "NO\n";
      return;
    }
  }
  int len = 0, p;
  for (int i = 1; i <= n; i++) {
    if (a[1][i] && a[2][i]) {
      len++;
      if (len == 1) {
        
      }
    } else {
      
      len = 0;
    }
  }
  std::cout << "YES\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}