#include <iostream>

// using namespace std;
using ll = long long;
using std::cin;
using std::cout;
using std::endl;

int n, m;

ll getDivisorsSum(int num) {
	if (num <= 1) return num;
	ll ans = 0;
	for (ll l = 1, r; l <= num; l = r + 1) {
		r = num / (num / l), ans += (ll) (num / l) * (l + r) * (r - l + 1) / 2;
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	cout << (getDivisorsSum(m) - getDivisorsSum(n - 1)) << endl;
	return 0;
}