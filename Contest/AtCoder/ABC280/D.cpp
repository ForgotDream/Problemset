#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

long long k, n;
vector<int> prime, prime_factor, prime_count;
bool is_not_prime[(int)1e7 + 50];

void get_prime() {
	for (long long i = 2; i * i <= k; i++) {
		if (is_not_prime[i]) continue;
		prime.push_back(i);
		for (long long j = i * i; j * j <= k; j += i) is_not_prime[j] = true;
	}
	return;
}

void divide() {
	for (auto i : prime) {
		int t = 0;
		while (k % i == 0) t++, k /= i;
		if (t) prime_factor.push_back(i), prime_count.push_back(t);
	}
	return;
}

void solve() {
	get_prime();
	divide();
	for (int i = 0; i < prime_factor.size(); i++) cout << prime_factor[i] << ' ' << prime_count[i] << endl;
	return;
}

int main() {
	cin >> k;
	solve();
	return 0;
}