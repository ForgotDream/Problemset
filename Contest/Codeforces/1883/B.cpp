#include <iostream>

using i64 = long long;

constexpr int SIG = 26;
int n, k, cnt[SIG];
void solve() {
  std::cin >> n >> k;
  for (int i = 0; i < SIG; i++) cnt[i] = 0;
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c;
    cnt[c - 'a']++;
  }
  int odd = 0;
  for (int i = 0; i < 26; i++) odd += (cnt[i] & 1);
  if ((n - k) & 1) {
    if ((odd - 1) > k || !((k - odd) & 1)) std::cout << "NO\n";
    else std::cout << "YES\n";
  } else {
    if (odd > k || ((k - odd) & 1)) std::cout << "NO\n";
    else std::cout << "YES\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
