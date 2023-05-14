#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s, t;
  std::cin >> s >> t;

  int n = s.length(), c1 = 0, c2 = 0;
  std::vector<int> b1(26), b2(26);
  for (int i = 0; i < n; i++) {
    if (s[i] != '@') {
      b1[s[i] - 'a']++;
    } else {
      c1++;
    }
    if (t[i] != '@') {
      b2[t[i] - 'a']++;
    } else {
      c2++;
    }
  }

  std::string p = "atcoder";

  int t1 = 0, t2 = 0;
  for (int i = 0; i < 26; i++) {
    if (std::count(p.begin(), p.end(), char(i + 'a')) == 0) {
      if (b1[i] != b2[i]) {
        std::cout << "No\n";
        return 0;
      }
    } else if (b1[i] > b2[i]) {
      t2 += b1[i] - b2[i];
    } else if (b1[i] < b2[i]) {
      t1 += b2[i] - b1[i];
    }
  }

  if (t1 > c1 || t2 > c2) {
    std::cout << "No\n";
    return 0;
  }

  std::cout << "Yes\n";

  return 0;
}