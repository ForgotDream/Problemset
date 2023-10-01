#include <cstring>
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;

constexpr int N = 1e6 + 50;
int n, m, a[N];
namespace N_M_LESS_THAN_7000 {
constexpr int M = 7050;
int cnt[M];
void solve() {
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    std::memset(cnt, 0, sizeof(cnt));
    for (int j = i + m - 1, t = 1; j <= n; j += m, t++) {
      for (int k = j - m + 1; k <= j; k++) cnt[a[k]]++;
      bool flg = true;
      for (int k = 1; k <= m; k++) {
        if (cnt[k] != t) {
          flg = false;
          break;
        }
      }
      if (flg) ans++;
    }
  }
  std::cout << ans << "\n";
}
}
namespace N_LESS_THAN_7E4 {
constexpr u64 base = 1e6 + 7;
u64 hash[N], pw[N];
void init() {
  pw[0] = 1;
  for (int i = 1; i < N; i++) pw[i] = base * pw[i - 1];
}
void solve() {
  init();
  i64 ans = 0;
  u64 curHash = 0, st = 0;
  for (int i = 1; i <= m; i++) curHash += pw[a[i]], st += pw[i];
  hash[1] = curHash;
  for (int i = 2; i <= n - m + 1; i++) {
    curHash -= pw[a[i - 1]];
    curHash += pw[a[i + m - 1]];
    hash[i] = curHash;
  }
  for (int i = 1; i <= n; i++) {
    u64 cur = 0;
    for (int j = i + m - 1, t = 1; j <= n; j += m, t++) {
      cur += hash[j - m + 1];
      if (t * st == cur) ans++;
    }
  }
  std::cout << ans << "\n";
}
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  if (n <= 7000) {
    N_M_LESS_THAN_7000::solve();
  } else {
    N_LESS_THAN_7E4::solve();
  }
}

int main() {
  std::freopen("st.in", "r", stdin);
  std::freopen("st.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
