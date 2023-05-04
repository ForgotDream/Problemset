#include <iostream>
#include <algorithm>

int main(int argc, char *argv[]) {
	std::cout << sizeof(std::pair<int, int>) / sizeof(int) << "\n";
	return 0;
}