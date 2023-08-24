#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 10;
int n, m, X[N], Y[N];
int a[N][N];
void remove(int idx) {
  for (int i = 1; i <= n; i++) a[X[idx]][i]--, a[i][Y[idx]]--;
  a[X[idx]][Y[idx]]++;
}
void recover(int idx) {
  for (int i = 1; i <= n; i++) a[X[idx]][i]++, a[i][Y[idx]]++;
  a[X[idx]][Y[idx]]--;
}
bool check(int idx) {
  remove(idx);
  for (int i = 1; i <= m; i++) {
    if (i == idx) continue;
    if (a[X[i]][Y[i]] > 1) return recover(idx), false;
  }
  for (int i = 1; i <= n; i++) {
    if (i == Y[idx]) continue;
    if (!a[X[idx]][i]) return recover(idx), true;
  }
  for (int i = 1; i <= n; i++) {
    if (i == X[idx]) continue;
    if (!a[i][Y[idx]]) return recover(idx), true;
  }
  recover(idx);
  return false;
}
void solve() {
  std::memset(a, 0, sizeof(a));
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    std::cin >> X[i] >> Y[i];
    a[X[i]][Y[i]] = -1;
    for (int j = 1; j <= n; j++) a[X[i]][j]++, a[j][Y[i]]++;
  }
  for (int i = 1; i <= m; i++) {
    if (check(i)) {
      std::cout << "YES\n";
      return;
    }
  }
  std::cout << "NO\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}