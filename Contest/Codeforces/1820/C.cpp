#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  if (std::count(a.begin(), a.end(), 0) == 0) {
    std::cout << "Yes\n";
    return;
  } 
  if (n == 1) {
    std::cout << "No\n";
    return;
  }

  auto b = a;
  std::sort(b.begin(), b.end());

  int mex = -1, semi;
  for (int i = 1; i < n; i++) {
    if (b[i] - b[i - 1] >= 2)  {
      if (b[i] - b[i - 1] > 2) {
        std::cout << "Yes\n";
        return;
      }
      mex = b[i - 1] + 1;
      semi = b[i];
      break;
    }
  }

  if (mex == -1) {
    if (b[n - 1] != n - 1) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
    return;
  }

  int l = 0, r = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == semi) {
      l = i;
      break;
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] == semi) {
      r = i;
      break;
    }
  }

  std::vector<int> s1(n + 50), s2(n + 50);
  for (int i = 0; i < n; i++) {
    if (a[i] < mex) {
      s1[a[i]]++;
      if (l <= i && i <= r) {
        s2[a[i]]++;
      }
    }
  }

  for (int i = 0; i < mex; i++) {
    if (s1[i] == s2[i]) {
      std::cout << "No\n";
      return;
    }
  }

  std::cout << "Yes\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}