/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

std::vector<int> init(int m, int k, std::vector<bool> &valid) {
  std::vector<int> res;
  valid.resize(1 << m);
  for (int i = 0; i < (1 << m); i++) {
    int cur = 0;
    bool flg = true;
    for (int j = 0; j < m; j++) {
      if (i & (1 << j)) {
        cur++;
        if (cur > k) {
          flg = false;
          break;
        }
      } else {
        cur = 0;
      }
    }
    if (flg) { res.push_back(i), valid[i] = true; }
  }
  return res;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  i64 n;
  int m, k;
  std::cin >> n >> m >> k;

<<<<<<< Updated upstream
  int d = (1 << (m - 1)) - 1;

  std::vector<bool> valid;
  auto stt = init(m, k, valid);

  auto print = [&](int num) {
    for (int i = 0; i < 5; i++) {
      std::cerr << (num & 1) << " \n"[i == 4];
      num >>= 1;
    }
  };

  for (auto i : stt) {
    print(i);
  }

  i64 ans = 0;
  
  for (auto sst : stt) {
    std::vector f(n, std::vector<i64>(1 << m));
    for (auto cst : stt) {
      int lst = (cst & d) << 1, rst = (cst & d) << 1 | 1;
      if (lst == sst || rst == sst) { f[0][cst] = 1; }
    }
    for (int i = 1; i < n; i++) {
      for (auto cst : stt) {
        int lst = (cst & d) << 1, rst = (cst & d) << 1 | 1;
        (f[i][cst] += f[i - 1][lst]) %= mod;
        (f[i][cst] += f[i - 1][rst]) %= mod;
      }
    }
    (ans += f[n - 1][sst]) %= mod;
  }

  std::cout << ans << "\n";
=======
  for (int i = 0; i < n; i++) {
    
  }

  std::vector<std::vector<int>> f;
>>>>>>> Stashed changes

  return 0;
}