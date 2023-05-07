#include <bits/stdc++.h>

int main() {
  std::string s1 = "BXCM", s2 = ".out";
  int cnt = 0;

  std::ofstream out;

  while (cnt < 10) {
    cnt++;
    out.open(s1 + std::to_string(cnt) + s2, std::ios::out);
    if (out.is_open()) {
      out.close();
    }
  }

  return 0;
}