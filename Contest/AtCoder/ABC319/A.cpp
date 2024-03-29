#include <string>
#include <iostream>
#include <map>

using i64 = long long;

std::map<std::string, int> mp{
    {"tourist", 3858},   {"ksun48", 3679},  {"Benq", 3658},
    {"Um_nik", 3648},    {"apiad", 3638},   {"Stonefeang", 3630},
    {"ecnerwala", 3613}, {"mnbvmar", 3555}, {"newbiedmy", 3516},
    {"semiexp", 3481},
};
void solve() {
  std::string s;
  std::cin >> s;
  std::cout << mp[s] << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}