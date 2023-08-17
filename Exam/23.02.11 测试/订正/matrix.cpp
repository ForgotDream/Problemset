#include <bits/stdc++.h>

static const double EPS = 1e-6; 

using namespace std;
double a, b, c, d;
double ans;

bool check(double mid) {
	double l1 = min(min((a - mid) * (d - mid), (a + mid) * (d + mid)), 
					min((a - mid) * (d + mid), (a + mid) * (d - mid)));
	double r1 = max(max((a - mid) * (d - mid), (a + mid) * (d + mid)), 
					max((a - mid) * (d + mid), (a + mid) * (d - mid)));
	
	double l2 = min(min((b - mid) * (c - mid), (b + mid) * (c + mid)), 
					min((b - mid) * (c + mid), (b + mid) * (c - mid)));
	double r2 = max(max((b - mid) * (c - mid), (b + mid) * (c + mid)), 
					max((b - mid) * (c + mid), (b + mid) * (c - mid)));
	
	if (r1 + EPS <= l2 || r2 + EPS <= l1) return false;
	else return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> a >> b >> c >> d;

	double l = 0, r = 2e9;
	while (l + EPS <= r) {
		double mid = (l + r) / 2;
		if (check(mid)) ans = mid, r = mid;
		else l = mid;
	}

	cout << fixed << setprecision(3) << ans << '\n';
	return 0;
}