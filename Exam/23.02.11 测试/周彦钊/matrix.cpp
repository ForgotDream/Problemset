#include <iostream>
#include <iomanip>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;

i64 a[3][3];
double ans;

// Idea: 	对于四个元素，这个差的绝对值都相等
// Proof:  	原本写了一大堆废话，现在全删了，我不知道怎么证，但主观意义上感觉应该很接近答案，能多骗一分是一分吧。 

int main() {
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> a[1][1] >> a[1][2] >> a[2][1] >> a[2][2];
	if (a[1][1] * a[2][2] > a[1][2] * a[2][1])
		swap(a[1][1], a[1][2]), swap(a[2][1], a[2][2]);
	
	ans = (double) (a[1][2] * a[2][1] - a[1][1] * a[2][2]) / (a[1][1] + a[1][2] + a[2][1] + a[2][2]);
	
	cout << fixed << setprecision(4) << ans << '\n';
	return 0;
}
