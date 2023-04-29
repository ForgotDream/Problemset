#include <iostream>
#include <cstdio>

using namespace std;

int H, M;
int h_t, h_o, m_t, m_o;

bool valid(int i, int j, int l, int k) {
	// cout << i << j << l << k << endl;
	if (i * 10 + l <= 23 && j * 10 + k <= 59) return true;
	else return false;
}

void solve() {
	int i, j, l, k;
	int h = H, m = M;
	for (; h <= 23; h++) {
		for (m = (h == H) ? M : 0; m <= 59; m++) {
			h_t = h / 10, h_o = h % 10;
			m_t = m / 10, m_o = m % 10;
			if (valid(h_t, h_o, m_t, m_o)) {
				cout << h_t << h_o << ' ' << m_t << m_o << endl;
				return;
			}
		}
	}
	cout << "00 00" << endl;
	return;
}

int main() {
	cin >> H >> M;
	solve();
	return 0;
}