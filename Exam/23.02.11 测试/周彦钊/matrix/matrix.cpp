#include <iostream>
#include <iomanip>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;

i64 a[3][3];
double ans;

// Idea: 	�����ĸ�Ԫ�أ������ľ���ֵ�����
// Proof:  	ԭ��д��һ��ѷϻ�������ȫɾ�ˣ��Ҳ�֪����ô֤�������������ϸо�Ӧ�úܽӽ��𰸣��ܶ�ƭһ����һ�ְɡ� 

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
