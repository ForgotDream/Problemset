#include <bits/stdc++.h>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const ldouble eps = 1e-11;
const int N = 1e5 + 5;
int n;
int L[N], X[N], V[N];
ldouble pos[N];
inline bool check(ldouble mid) {
  pos[n] = X[n] - V[n] * mid;
  for (int i = n - 1; i >= 0; i--)
    pos[i] = std::max(X[i] - V[i] * mid, pos[i + 1] + L[i + 1]);
  return pos[0] <= 0;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  while (T--) {
    std::cin >> n;
    for (int i = 0; i <= n; i++) std::cin >> L[i];
    for (int i = 0; i <= n; i++) std::cin >> X[i];
    for (int i = 0; i <= n; i++) std::cin >> V[i];
    ldouble l = 0, r = 1e9;
    while (r - l > eps) {
      ldouble mid = (l + r) / 2;
      if (check(mid))
        r = mid;
      else
        l = mid;
    }
    std::cout << std::fixed << std::setprecision(10) << l << '\n';
  }
  return 0;
}
