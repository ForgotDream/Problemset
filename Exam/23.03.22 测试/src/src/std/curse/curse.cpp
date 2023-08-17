#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	freopen("curse.in", "r", stdin);
	freopen("curse.out", "w", stdout);
	int n, b[1001], l;
	scanf("%d", &n);
	memset(b, 0, sizeof(b));
	for (int i = 1; i <= n; i++)
	{
		char s[1001];
		scanf("%s", s);
		l = strlen(s);
		for (int i = 0; i < l; i++)
		    if (s[i] == '1') b[i+1]++;
	}
	for (int i = 1; i <= l; i++)
	    if (b[i] > n/2) printf("1"); else printf("0");
	printf("\n");
	return 0; 
}
