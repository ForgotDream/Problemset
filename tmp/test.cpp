#include <iostream>
#include <queue>
#include <random>
#include <chrono>

int main() {
	std::priority_queue<
		std::pair<int, int>,
		std::vector<std::pair<int, int>>,
		std::greater<std::pair<int, int>>
	> pq;

	std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < 10; i++) {
		int w = rnd();
		pq.emplace(1, w);
		std::cout << w << " \n"[i == 9];
	}

	while (!pq.empty()) {
		std::cout << pq.top().second << "\n";
		pq.pop();
	}

	return 0;
}