#include <bits/stdc++.h>
#define int long long
#define inf 1000000000
#define mp(a, b) \
  (pair<int, int>) { a, b }
#define mk(a, b, c) \
  (hm) { a, b, c }
#define se second
#define fi first
using namespace std;
int n, m, k, ansl[200005], ansc[200005];
multiset<pair<int, int> > s;
struct hm {
  int x, t, id;
} a[200005];
vector<hm> t;
bool cmp(hm a, hm b) { return a.x == b.x ? a.t < b.t : a.x < b.x; }
int ask(int x) {
  int l = 1, r = k, mid;
  while (l < r) {
    mid = (l + r) >> 1;
    if (t[mid].x + t[mid].t >= x) r = mid;
    else l = mid + 1;
  }
  if (t[l].x <= x && t[l].x + t[l].t >= x) return l;
  return 0;
}
void clr(int x) {
  for (; x < k;) {
    if (t[x + 1].x + t[x + 1].t <= t[x].x + t[x].t) t.erase(t.begin() + x + 1), k--;
    else break;
  }
}
signed main() {
  t.push_back(mk(0, 0, 0));
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    scanf("%lld %lld", &a[i].x, &a[i].t), a[i].id = i, ansl[i] = a[i].t;
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1, mx = 0; i <= n; i++) {
    if (a[i].x + a[i].t > mx) {
      t.push_back(a[i]);
      k++;
      mx = a[i].x + a[i].t;
    }
  }
  for (int i = 1, l, sz; i <= m; i++) {
    scanf("%lld %lld", &l, &sz);
    int p = ask(l);
    if (p) {
      ansl[t[p].id] += sz;
      t[p].t += sz;
      ansc[t[p].id]++;
      while (!s.empty()) {
        auto it = s.lower_bound(mp(t[p].x, -192));
        if ((it == s.end()) || (t[p].x + t[p].t < (it->fi))) break;
        ansl[t[p].id] += (it->se);
        t[p].t += (it->se);
        ansc[t[p].id]++;
        s.erase(it);
      }
      clr(p);
    } else
      s.insert(mp(l, sz));
  }
  for (int i = 1; i <= n; i++) printf("%lld %lld\n", ansc[i], ansl[i]);
  return 0;
}
