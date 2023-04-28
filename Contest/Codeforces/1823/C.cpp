#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> getPrime(int n) {
  std::vector<int> prime;
  std::vector<bool> isNotPrime(n + 1);

  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) {
      prime.push_back(i);
    }
    for (int j = 0; j < prime.size() && (i64) prime[j] * i <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        break;
      }
    }
  }

  return prime;
}
  
static const std::vector<int> prime = getPrime(1e5 + 50);

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  std::map<int, int> factor;

  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    
    int pivot = 0, pre = a[i];
    while (prime[pivot] * prime[pivot] <= pre && a[i] != 1) {
      while (a[i] % prime[pivot] == 0) {
        a[i] /= prime[pivot];
        factor[prime[pivot]]++;
      }
      pivot++;
    }
    if (a[i] != 1) {
      factor[a[i]]++;
    }
  }

  int ans = 0;
  for (auto &i : factor) {
    ans += i.second / 2;
    i.second %= 2;
  }

  int rst = 0;
  for (auto i : factor) {
    rst += i.second;
  }

  if (ans != 0 || rst >= 3) {
    ans += rst / 3;
    std::cout << ans << "\n";
  } else {
    std::cout << 0 << "\n";
    return;
  }

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