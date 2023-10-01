#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using i64 = long long;

constexpr int pw[] = {1,      10,      100,      1000,      10000, 
                      100000, 1000000, 10000000, 100000000, 1000000000};
constexpr char o[] = {'*', '+', '-', '/'};
constexpr int N = 20;
std::string s;
std::vector<std::string> ans;
long double calc(int a, int b, char c) {
  if (c == '+') return a + b;
  else if (c == '-') return a - b;
  else if (c == '*') return 1ll * a * b;
  else return 1. * a / b;
}
struct Parser {
  int val, dig[N], len, cur, p;
  inline void init(int num) {
    p = 1, len = 0, val = num;
    while (num) dig[len++] = num % 10, num /= 10;
    cur = len - 1;
  }
  inline int next() {
    if (cur == -1) return -1;
    int res = val + pw[cur] * (p - dig[cur]);
    p++;
    if (p == 10) p = 0, cur--;
    if (res == 0) return -1;
    return res;
  }
} pa, pb, pc;
std::string cat(int a, char opt, int b, int c) {
  std::string res;
  res = std::to_string(a) + opt + std::to_string(b) + '=' + std::to_string(c);
  return res;
}
void get(int a, int b, int c, char opt) {
  int na, nb, nc;
  pa.init(a);
  while ((na = pa.next()) != -1) {
    for (auto no : o) {
      if (no >= opt) break;
      if (calc(na, b, no) == c) ans.push_back(cat(na, no, b, c));
    }
    pb.init(b);
    while ((nb = pb.next()) != -1) {
      if (calc(na, nb, opt) == c) ans.push_back(cat(na, opt, nb, c));
    }
    pc.init(c);
    while ((nc = pc.next()) != -1) {
      if (calc(na, b, opt) == nc) ans.push_back(cat(na, opt, b, nc));
    }
  }
}
void solve() {
  std::cin >> s;
  char opt;
  int st = 0;
  i64 a = 0, b = 0, c = 0;
  for (auto ch : s) {
    if ((st == 0 || st == 2 || st == 4) && !std::isdigit(ch)) {
      std::cout << "Format Error\n";
      return;
    } else if (st == 0) {
      a = ch - '0';
      st = 1;
    } else if (st == 1) {
      if (std::isdigit(ch)) {
        a = 10 * a + ch - '0';
      } else {
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
          std::cout << "Format Error\n";
          return;
        } else {
          opt = ch, st = 2;
        }
      }
    } else if (st == 2) {
      b = 10 * b + ch - '0';
      st = 3;
    } else if (st == 3) {
      if (std::isdigit(ch)) {
        b = 10 * b + ch - '0';
      } else {
        if (ch != '=') {
          std::cout << "Format Error\n";
          return;
        } else {
          st = 4;
        }
      }
    } else if (st == 4) {
      c = 10 * c + ch - '0';
    }
  }
  if (st != 4 || !a || !b || !c || a > 1e9 || b > 1e9 || c > 1e9) {
    std::cout << "Format Error\n";
  } else if (calc(a, b, opt) == c) {
    std::cout << "Correct\n";
  } else {
    i64 na = a, nb = b, nc = c;
    pa.init(a), pb.init(b), pc.init(c);
    i64 la = pa.len, lb = pa.len, lc = pc.len;
    for (int i = 1; i <= 9; i++) {
      nb = b / 10, nc = c + 1ll * pw[lc] * i;
      if (nb <= 0 || nc > 1e9) continue;
      if (calc(a, nb, opt) == nc) ans.push_back(cat(a, opt, nb, nc));
    }
    for (int i = 0; i <= 9; i++) {
      nb = 10 * b + i, nc = c - pc.dig[lc - 1] * pw[lc - 1];
      if (nb > 1e9 || nc <= 0) continue;
      for (auto no : o) {
        if (calc(a, nb, no) == nc) ans.push_back(cat(a, no, nb, nc));
      }
    }
    for (int i = 1; i <= 9; i++) {
      na = a / 10, nb = b + 1ll * pw[lb] * i;
      if (na <= 0 || nb > 1e9) continue;
      for (auto no : o) {
        if (calc(na, nb, no) == c) ans.push_back(cat(na, no, nb, c));
      }
    }
    for (int i = 0; i <= 9; i++) {
      na = 10 * a + i, nb = b - pb.dig[lb - 1] * pw[lb - 1];
      if (na > 1e9 || nb <= 0) continue;
      for (auto no : o) {
        if (calc(na, nb, no) == c) ans.push_back(cat(na, no, nb, c));
      }
    }
    get(a, b, c, opt);
    std::sort(ans.begin(), ans.end());
    if (ans.empty()) {
      std::cout << "Math Error\n";
    } else {
      std::cout << "Typo: " << s << " instead of " << ans[0] << "\n";
    }  
  }
}

int main() {
  std::freopen("inspect.in", "r", stdin);
  std::freopen("inspect.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
