#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, T, ans, f[5010][5010];
struct lmy{int t, p, f;};
lmy a[5010];

inline void cmax(int &a, int b) {a = a > b ? a : b;}
inline int power(int x) {return x * x;}

signed main()
{
  ios::sync_with_stdio(false),cin.tie(nullptr);
  cin >> n >> T;
  assert(n <= 800);
  for(int i = 1; i <= n; ++i) cin >> a[i].t >> a[i].p >> a[i].f;
  sort(a + 1, a + n + 1, [](lmy a, lmy b){return a.f < b.f;});
  memset(f, 0xcf, sizeof f);
  for(int i = 1; i <= n; ++i) f[i][a[i].t] = a[i].p;
  for(int i = 1; i <= n; ++i) for(int j = T; j >= a[i].t; --j)
  {
  	for(int k = 1; k < i; ++k) cmax(f[i][j], f[k][j - a[i].t] - power(a[k].f) + 2 * a[i].f * a[k].f - power(a[i].f) + a[i].p);
  }
  for(int i = 1; i <= n; ++i) for(int j = 0; j <= T; ++j) cmax(ans, f[i][j]);
  cout << ans << '\n';
}
