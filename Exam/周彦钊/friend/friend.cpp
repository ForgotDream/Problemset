#include <iostream>

using i64 = long long;

constexpr int N = 2e6 + 50, mod = 1 << 24;
int n, k, b, p, d[N];
template<int N = 1 << 25, int SIG = 2>
struct Trie {
  int nxt[N][2], cnt;
  void insert(int num) {
    int pivot = 0;
    for (int i = 23; i >= 0; i--) {
      int d = !!(num & (1 << i));
      if (!nxt[pivot][d]) nxt[pivot][d] = ++cnt;
      pivot = nxt[pivot][d];
    }
  }
  int query(int num) {
    int res = 0, pivot = 0;
    for (int i = 23; i >= 0; i--) {
      int d = !(num & (1 << i));
      if (nxt[pivot][d]) res += 1 << i, pivot = nxt[pivot][d];
      else pivot = nxt[pivot][!d];
    }
    return res;
  }
};
Trie<> trie;

signed main() {
  std::freopen("friend.in", "r", stdin);
  std::freopen("firend.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k >> b >> p;
  
  d[1] = p, trie.insert(d[1]);
  for (int i = 2; i <= n; i++) {
    d[i] = (1ll * k * d[i - 1] + b) % mod;
    trie.insert(d[i]);
  }

  int ans = 0, pw = 1;
  for (int i = 1; i <= n; i++) {
    int cur = trie.query(d[i]);
    (ans += 1ll * pw * cur % mod) %= mod;
    (pw *= 3) %= mod;
  }
  std::cout << ans << "\n";

  return 0;
}