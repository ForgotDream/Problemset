/*
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using f64 = double;

constexpr int D = 550, P = 20;
constexpr int prime[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                         31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

int n, m, d[D];

f64 logp[P], f[D][P]; 
int pre[D][P];

int num[100050], len;

template <typename T>
inline bool chkmin(T &a, const T &b) { return a > b ? a = b, true : false; }

void mul(int p) {
  int v = 0;
  for (int i = 0; i < len; i++) {
    v = (num[i] = num[i] * p + v) / 10;
    num[i] %= 10;
  }
  while (v) num[len++] = v % 10, v /= 10;
}

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) if (!(n % i)) d[m++] = i;

  for (int i = 0; i < P; i++) logp[i] = std::log(prime[i]);
  for (int i = 1; i < m; i++) {
    for (int j = 0; j < P; j++) f[i][j] = 1e9;
    for (int j = 0; j < i; j++) {
      if (!(d[i] % d[j])) {
        int t = d[i] / d[j];
        for (int k = 1; k < 20; k++) {
          if (chkmin(f[i][k], f[j][k - 1] + logp[k - 1] * (t - 1))) {
            pre[i][k] = j;
          }
        }
      }
    }
    // ugly brackets need some empty lines to beautify
  }

  num[0] = len = 1;
  int p = std::min_element(f[m - 1], f[m - 1] + P) - f[m - 1];
  for (int i = m - 1; i; i = pre[i][p], p--) {
    for (int j = 1; j < d[i] / d[pre[i][p]]; j++) mul(prime[p - 1]);
  }

  while (len--) std::cout << num[len];
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
