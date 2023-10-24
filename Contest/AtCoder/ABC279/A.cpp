#include <iostream>
#include <cstdio>
#include <string>

std::string str;
int ans;

int main() {
	std::cin >> str;
	for (int i = 0; i < str.length(); i++) if (str[i] == 'v') ans++; else ans += 2;
	std::cout << ans << std::endl;
	return 0;
}