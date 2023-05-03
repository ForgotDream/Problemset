#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);

  std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
  std::string s1 = "B", s2 = ".in";
  std::ofstream out;

  for (int i = 1; i <= 20; i++) {
    out.open(("data\\" + s1 + std::to_string(i) + s2).data(), std::ios::out);

    if (out.is_open()) {
      int n;

      if (i > 10 && i <= 14) {
        n = rnd() % ((int)1e6 - 20000) + 20000;
        out << n << "\n";
        for (int i = 0; i < n; i++) {
          out << 1 << " \n"[i == n - 1];
        }
      } else {
        if (i <= 4) {
          n = 4;
        } else if (i <= 10) {
          n = 10;
        } else {
          n = 1e6;
        }

        out << n << "\n";

        std::vector<int> a(n);
        std::generate(a.begin(), a.end(), [&]() {
          int res = rnd() % 10;
          return res;
        });

        for (int i = 0; i < n; i++) {
          out << a[i] << " \n"[i == n - 1];
        }
      }

      out.close();
    }
  }

  return 0;
}