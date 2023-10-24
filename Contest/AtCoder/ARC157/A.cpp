#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int n, a, b, c, d;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> a >> b >> c >> d;

  if (n == 1 || n == 2) {
    cout << "Yes" << '\n';
    return 0;
  }

  if (abs(b - c) > 1) {
    cout << "No" << '\n';
    return 0;
  }

  if (a && d && !b && !c) {
    cout << "No" << '\n';
    return 0;
  }

  cout << "Yes" << '\n';

  return 0;
}