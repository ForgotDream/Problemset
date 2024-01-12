/*
 * @file    CF1582G Kuzya and Homework.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-01-08
 */
#include <bits/stdc++.h>

using i64 = long long;
using pil = std::pair<int, i64>;

constexpr int N = 1e6 + 50;
int n, a[N];

int prime[N], cnt;
bool isNotPrime[N];
void getPrime(int n) {
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}

std::vector<int> fac[N];
int lp[N];

void mul(int cur, int pos) {
  for (int i = 1; i <= cnt && prime[i] * prime[i] <= cur; i++) {  
    while (cur % prime[i] == 0) fac[prime[i]].push_back(pos), cur /= prime[i];
  }
  if (cur > 1) fac[cur].push_back(pos);
}

void divide(int cur, int pos) {
  for (int i = 1; i <= cnt && prime[i] * prime[i] <= cur; i++) {
    while (cur % prime[i] == 0) {
      if (fac[prime[i]].empty()) return lp[pos] = 0, void();
      lp[pos] = std::min(lp[pos], fac[prime[i]].back());
      cur /= prime[i], fac[prime[i]].pop_back();
    }
  }
  if (cur > 1) {
    if (fac[cur].empty()) return lp[pos] = 0, void();
    lp[pos] = std::min(lp[pos], fac[cur].back()), fac[cur].pop_back();
  }
}

void solve() {
  getPrime(1e6);

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c, lp[i] = i;
    if (c == '*') mul(a[i], i);
    else divide(a[i], i);
  }

  i64 ans = 0;
  std::stack<pil, std::vector<pil>> st;
  for (int i = n; i >= 1; i--) {
    i64 cur = 1;
    while (!st.empty() && st.top().first >= lp[i]) {
      cur += st.top().second;
      st.pop();
    }
    st.emplace(lp[i], cur);
    if (lp[i] == i) ans += cur;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
