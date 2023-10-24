/**
 * @file    P8289 预处理器.cpp
 * @author  ForgotDream
 * @brief   模拟
 * @date    2023-03-19
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

bool check(char c) {
  return std::isdigit(c) || std::isalpha(c) || c == '_' || c == '#';
}

const std::vector<std::string> split(const std::string &s) {
  std::vector<std::string> res;

  int len = s.length();
  std::string cur;
  for (int i = 0; i < len; i++) {
    if (s[i] == ' ') {
      res.push_back(cur);
      cur = "";
    } else {
      cur += s[i];
    }
  }

  if (cur != "") {
    res.push_back(cur);
  }

  return res;
}

const std::vector<std::pair<std::string, bool>> part(const std::string &s) {
  std::vector<std::pair<std::string, bool>> res;

  bool status = true;
  int len = s.length();

  std::string cur;
  for (int i = 0; i < len; i++) {
    if (status && !check(s[i])) {
      res.emplace_back(cur, status);
      status = !status;
      cur = s[i];
    } else if (!status && check(s[i])) {
      res.emplace_back(cur, status);
      status = !status;
      cur = s[i];
    } else {
      cur += s[i];
    }
  }

  if (cur != "") {
    res.emplace_back(cur, status);
  }

  return res;
}

const std::string unite(const std::vector<std::string> &v) {
  std::string res;

  for (int i = 0; i < v.size(); i++) {
    res += v[i];
    if (i != v.size() - 1) {
      res += " ";
    }
  }

  return res;
}

const std::string parse(const std::string &s, const std::map<std::string, std::string> &mp) {
  static std::map<std::string, bool> used;
  std::string res;

  auto out = part(s);

  for (auto i : out) {
    auto curStr = i.first;
    auto curStatus = i.second;
    if (curStatus) {
      if (mp.count(curStr) && (!used.count(curStr) || !used[curStr])) {
        used[curStr] = true;
        res += parse(mp.at(curStr), mp);
        used[curStr] = false;
      } else {
        res += curStr;
      }
    } else {
      res += curStr;
    }
  }

  return res;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::cin.get();

  std::map<std::string, std::string> mp;
  for (int i = 0; i < n; i++) {
    std::string s;
    std::getline(std::cin, s);

    auto v = split(s);
    if (v[0] == "#define") {
      std::vector<std::string> tmp(v.begin() + 2, v.end());
      mp[v[1]] = unite(tmp);
      std::cout << "\n";
    } else if (v[0] == "#undef") {
      mp.erase(v[1]);
      std::cout << "\n";
    } else {
      for (int j = 0; j < v.size(); j++) {
        std::cout << parse(v[j], mp) << " \n"[j == v.size() - 1];
      }
    }

  }

  return 0;
}