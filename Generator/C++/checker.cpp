#include <bits/stdc++.h>
#include <windows.h>

using i64 = long long;

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  int cnt;
  std::string name = argv[1];
  if (argc == 3) {
    cnt = std::atoi(argv[2]);
  } else {
    cnt = 10;
  }

  for (int i = 1; i <= cnt; i++) {
    system((".\\v.exe " + name + std::to_string(i)).data());
  }

  return 0;
}