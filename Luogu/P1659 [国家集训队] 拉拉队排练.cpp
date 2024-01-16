/*
 * @file    P1659 [国家集训队] 拉拉队排练.cpp
 * @author  ForgotDream
 * @brief   PAM
 * @date    2024-01-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 50, mod = 19930726;

struct PAM {
  int ch[N][26], len[N], nxt[N], cnt[N], tot, siz, lst;
  char s[N];
  void init() {
    lst = tot = 0, siz = -1;
    newNode(0), newNode(-1), nxt[0] = 1;
  }
  int newNode(int l) {
    len[++siz] = l, nxt[siz] = 0;
    memset(ch[siz], 0, sizeof(ch[siz]));
    return siz;
  }
  int getNxt(int u) {
    while (s[tot - len[u] - 1] != s[tot]) u = nxt[u]; 
    return u;
  }
  void expand(char c) {
    s[++tot] = c;
    int cur = getNxt(lst), d = c - 'a';
    if (!ch[cur][d]) {
      int p = newNode(len[cur] + 2);
      nxt[p] = ch[getNxt(nxt[cur])][d];
      ch[cur][d] = p;
    }
    lst = ch[cur][d], cnt[lst]++;
  }
} pam;

int n;
i64 k;
char s[N];

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

int p[N];

void solve() {
  std::cin >> n >> k >> (s + 1);
  pam.init();
  for (int i = 1; i <= n; i++) pam.expand(s[i]);

  for (int i = pam.siz; ~i; i--) (pam.cnt[pam.nxt[i]] += pam.cnt[i]) %= mod;

  std::iota(p + 1, p + pam.siz + 1, 1);
  std::sort(p + 1, p + pam.siz + 1, [&](int lhs, int rhs) {
    return pam.len[lhs] > pam.len[rhs];
  });

  int piv = 1;
  i64 ans = 1;

  while (k) {
    // std::cerr << k << " " << ans << "\n";
    if (piv > pam.siz) return std::cout << -1 << "\n", void();
    int u = p[piv];
    if (pam.len[u] % 2 == 0) {
      piv++;
      continue;
    }
    if (pam.cnt[u] >= k) {
      ans *= fastPow(pam.len[u], k, mod), ans %= mod;
      std::cout << ans << "\n";
      return;
    } else {
      ans *= fastPow(pam.len[u], pam.cnt[u], mod), ans %= mod;
      k -= pam.cnt[u], piv++;
    }
  }
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
