#include <bits/stdc++.h>

using i64 = long long;

constexpr int encode[] = { 1, 10, 100, 1000, 10000 };

void solve() {
  std::string s;
  std::cin >> s;
  int n = s.length();
  std::vector<int> cnt(5), f(n);
  std::vector can(n, std::vector(5, std::vector<int>(5)));
  for (int i = n - 1; i >= 0; i--) {
    int lst = (i == n - 1 ? 0 : f[i + 1]), d = s[i] - 'A';
    bool flg = true;
    for (int j = d + 1; j < 5; j++) {
      if (cnt[j]) {
        flg = false;
        break;
      }
    }
    if (flg) {
      f[i] = lst + encode[d];
    } else {
      f[i] = lst - encode[d];
    }
    cnt[d]++;
  }
  // 计算出前边有多少数字可用
  std::array<int, 5> wcnm { 0, 0, 0, 0, 0 };
  for (int i = 0; i < n; i++) {
    int d = s[i] - 'A';
    // 改成哪个数字
    for (int j = 0; j < 5; j++) {
      auto cur = wcnm;
      for (int k = 0; k < j; k++) { cur[k] = 0; }
      for (int k = 0; k < 5; k++) { can[i][j][k] = cur[k]; }
    }
    for (int j = 0; j < d; j++) { wcnm[j] = 0; }
    wcnm[d]++;
  }
  std::vector<int> ano(5);
  int ans = f[0];
  for (int i = n - 1; i >= 0; i--) {
    int d = s[i] - 'A', lst = (i == n - 1 ? 0 : f[i + 1]);
    cnt[d]--;
    // 枚举将当前位置改成哪个数
    for (int j = 0; j < 5; j++) {
      int cur = lst;
      bool cnm = true;
      ano[j]++;
      // 判断当前的符号
      for (int k = j + 1; k < 5; k++) {
        if (ano[k]) {
          cnm = false;
          break;
        }
      }
      if (cnm) {
        cur += encode[j];
      } else {
        cur -= encode[j];
      }
      // 计算前边的贡献
      for (int k = 0; k < 5; k++) {
        bool flg = true;
        for (int p = k + 1; p < 5; p++) {
          if (ano[p]) {
            flg = false;
            break;
          }
        }
        if (flg) {
          cur += can[i][j][k] * encode[k];
          cur -= (cnt[k] - can[i][j][k]) * encode[k];
        } else {
          cur -= cnt[k] * encode[k];
        }
      }
      ans = std::max(ans, cur);
      ano[j]--;
    }
    ano[d]++;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}