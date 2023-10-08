#include <bits/stdc++.h>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const int N = 1e5 + 5;
int n, m;
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin >> n >> m;
  std::vector<int> a(n), b(m);
  for (auto &x : a) std::cin >> x;
  std::sort(a.begin(), a.end(), [](auto x, auto y) { return x > y; });
  for (auto &x : b) std::cin >> x;
  std::sort(b.begin(), b.end(), [](auto x, auto y) { return x > y; });
  std::deque<ll> A, B;
  for (auto x : a) A.push_back(x);
  for (auto x : b) B.push_back(x);
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ll x = A.front() * B.front();
    ll y = A.back() * B.back();
    if (x > y) {
      ans += x;
      A.pop_front();
      B.pop_front();
    } else {
      ans += y;
      A.pop_back();
      B.pop_back();
    }
  }
  std::cout << ans;
  return 0;
}
