/*
 * @file    
 * @author  forgotdream
 * @brief   
 * @date    2024-02-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr i64 mod[] = {
	11,
	101,
	1001,
	10001,
	100001,
	1000001,
	10000001,
	100000001,
	1000000001ll,
	10000000001ll,
	100000000001ll,
	1000000000001ll,
	10000000000001ll,
	100000000000001ll,
	1000000000000001ll,
	10000000000000001ll,
	100000000000000001ll
};

void solve() {
	i64 n;
	std::cin >> n;

	std::vector<i64> a;

	for (auto i : mod) {
		if (n % i == 0) a.push_back(n / i);
	}

  std::cout << a.size() << "\n";

	std::reverse(a.begin(), a.end());
	for (int i = 0 ; i < a.size(); i++) {
		std::cout << a[i] << " \n"[i == a.size() - 1];
	}
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
