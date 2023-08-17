#include <iostream>

using namespace std;

int n, m, s, l, r;
int a[(int)1e5 + 50];

bool check(int x) {
  int sum = 0, i, k = 0;
  for (i = 1; i <= n; i++) {
    if (sum + a[i] <= x)
      sum += a[i];
    else
      sum = a[i], k++;
  }
  return k >= m;
}

void solve() {
  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid))
      l = mid + 1;
    else
      r = mid - 1;
  }
  cout << l << endl;
  return;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i], r += a[i], l = max(a[i], l);
  solve();
  return 0;
}