#include <bits/stdc++.h>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const int N = 1e5 + 5;
int n, m, cnt;
ll ans = 0, a[N], b[N];
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    cnt += (a[i] > 0);
  }
  for (int i = 1; i <= m; i++) std::cin >> b[i];
  std::sort(a + 1, a + n + 1, [](auto x, auto y) { return x > y; });
  std::sort(b + 1, b + m + 1, [](auto x, auto y) { return x > y; });
  std::deque<ll> A, B;
  for (int i = 1; i <= n; i++) A.push_back(a[i]);
  for (int i = 1; i <= m; i++) B.push_back(b[i]);
  for (int i = 1; i <= cnt; i++) {
    ans += A.front() * B.front();
    A.pop_front();
    B.pop_front();
  }
  for (int i = cnt + 1; i <= n; i++) {
    ans += A.back() * B.back();
    A.pop_back();
    B.pop_back();
  }
  std::cout << ans;
  return 0;
}
