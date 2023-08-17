#include <bits/stdc++.h>

using i64 = long long;

struct Node {
  int t, v;
  Node() {
    t = 0, v = 0;
    return;
  }
};

long double calc(long double mid, std::vector<Node> a) {
  long double minn, maxx;
  minn = (mid - a[0].t) * a[0].v;
  maxx = minn;

  for (int i = 1; i < a.size(); i++) {
    long double tmp = (mid - a[i].t) * a[i].v;
    minn = std::min(minn, tmp);
    maxx = std::max(maxx, tmp);
  }

  return maxx - minn;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  static const long double EPS = 1e-12;

  int n;
  std::cin >> n;

  long double l = 0, r = 1e15;

  std::vector<Node> a(n); 
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].t >> a[i].v;
    l = std::max(l, (long double) a[i].t);
  }

  while (r - l > EPS) {
    long double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
    std::cerr << lmid << " " << rmid << "\n";
    if (calc(lmid, a) < calc(rmid, a) + EPS) {
      r = rmid;
    } else {
      l = lmid;
    }
  }

  std::cout << std::fixed << std::setprecision(2) << calc(l, a) << "\n";

  return 0;
}