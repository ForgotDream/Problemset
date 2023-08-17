#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

const double eps = 1e-7;
bool flag = false;
ll ans[(int)1e7 + 50];
int maxd;
ll v[(int)1e7 + 50];
int a, b;

inline int get_first(ll a, ll b) { return b / a + 1; }

ll gcd(ll a, ll b) { return a % b == 0 ? b : gcd(b, a % b); }

bool better(int d) {
  for (int i = d; i >= 0; i--)
    if (v[i] != ans[i]) return ans[i] == -1 || v[i] < ans[i];
  return false;
}

bool dfs(int d, int from, ll aa, ll bb) {
  if (d == maxd) {
    if (bb % aa) return false;
    v[d] = bb / aa;
    if (better(d)) memcpy(ans, v, sizeof(ll) * (d + 1));
    return true;
  }
  bool ok = false;
  from = max(from, get_first(aa, bb));
  for (int i = from;; i++) {
    if (bb * (maxd + 1 - d) <= i * aa) break;
    v[d] = i;
    ll b2 = bb * i;
    ll a2 = aa * i - bb;
    ll g = gcd(a2, b2);
    if (dfs(d + 1, i + 1, a2 / g, b2 / g)) ok = true;
  }
  return ok;
}

int main() {
  cin >> a >> b;
  for (maxd = 1;; maxd++) {
    memset(ans, -1, sizeof(ans));
    if (dfs(0, get_first(a, b), a, b)) {
      flag = 1;
      break;
    }
  }
  for (int i = 0; i <= maxd; i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}