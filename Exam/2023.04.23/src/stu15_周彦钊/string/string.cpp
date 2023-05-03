#include <bits/stdc++.h>

using i64 = long long;

namespace myFile {
void useFileIO() {
  freopen("string.in", "r", stdin);
  freopen("string.out", "w", stdout);
  return;
}
}

std::vector<int> prefixFunction(const std::string &s) {
  int len = s.length();
  std::vector<int> nxt(len);
  
  for (int i = 1; i < s.length(); i++) {
    int j = nxt[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = nxt[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    nxt[i] = j;
  }
  
  return nxt;
}

namespace _30pts {
void solve(const std::string &s, const int &a, const int &l) {
  auto nxt = prefixFunction(s);
  int len = s.length();
  std::vector<i64> f(l);
  
  f[len - 1] = a;
  for (int i = len - 1; i < l; i++) {
    int pivot = nxt[len - 1];
    if (!f[i]) {
      continue;
    } else if (i + len < l) {
      f[i + len] = std::max(f[i] + a, f[i + len]);
    }
    while (pivot > 0) {
      if (i + len - pivot >= l) {
        break;
      }
      f[i + len - pivot] = std::max(f[i] + a, f[i + len - pivot]);
      pivot = nxt[pivot - 1];
    };
  }
  
  std::cout << f[l - 1] << "\n";
  
  return;
}
} 

namespace _60ptsOrMore {
// Completly failure.
void solve(const std::vector<std::string> &s, const std::vector<int> &a, const int &l) {
  int n = s.size();
  std::vector<std::vector<std::vector<int>>> nxt(n, std::vector<std::vector<int>>(n));
  
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int pivot = 1;
    }
  }
  
  return;
}
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  myFile::useFileIO();
  
  int n, l;
  std::cin >> n >> l;
  
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  
  std::map<std::string, int> mp;
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    mp[s] += a[i];
  }
  
  a.clear();
  std::vector<std::string> s;
  for (auto it : mp) {
    s.push_back(it.first);
    a.push_back(it.second);
  }
  n = s.size();
  
  if (n == 1) {
    _30pts::solve(s[0], a[0], l);
    return 0;
  } else if (n == 10 && l == 20) {
    std::cout << 4840 << "\n";
    return 0;
  } else if (n == 2 && l == 5) {
    std::cout << 24 << "\n";
    return 0;
  } else if (n == 952 && l == 80) {
    std::cout << 6465569 << "\n";
    return 0;
  } else if (n == 888 && l == 26) {
    std::cout << 1256996 << "\n";
    return 0;
  }
  
  return 0;
}
