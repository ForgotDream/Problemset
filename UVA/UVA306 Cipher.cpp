/**
 * @file    UVA306 Cipher.cpp
 * @author  ForgotDream
 * @brief   置换
 * @date    2023-03-03
 */
#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (true) {
    int n;
    std::cin >> n;

    if (n == 0) {
      break;
    }

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      std::cin >> a[i];
    }

    std::vector<int> round[n + 1];
    std::vector<int> blg(n + 1), pos(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (blg[i]) {
        continue;
      }
      int pivot = i, cur = 0;
      ++cnt;
      do {
        blg[pivot] = cnt;
        pos[pivot] = cur++;
        round[cnt].push_back(pivot);
        pivot = a[pivot];
        // std::cerr << pivot << "\n";
      } while (pivot != i);
    }

    while (true) {
      int len;
      std::cin >> len;
      // std::cerr << len << "\n";
      if (len == 0) {
        break;
      }
      std::string s, ans = "";
      ans.resize(n);
      // std::cerr << ans.size() << "\n";
      
      // char ch = getchar();
      std::getline(std::cin, s);
      s = s.substr(1, s.length() - 1);
      for (int i = s.length() + 1; i <= n; i++) {
        s += " ";
      }
      // std::cerr << s << "\n";

      for (int i = 1; i <= n; i++) {
        auto cur = round[blg[i]];
        // std::cerr << cur[(pos[i] + len) % cur.size()] - 1 << "\n";
        ans[cur[(pos[i] + len) % cur.size()] - 1] = s[i - 1];
      }

      std::cout << ans << "\n";
      // std::cerr << ans << "\n";
    }

    std::cout << "\n";
  }

  return 0;
}