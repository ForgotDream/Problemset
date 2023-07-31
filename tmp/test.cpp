#include <stdio.h>

#define H_MAX 2000
#define W_MAX 2000

<<<<<<< Updated upstream
int main() {
  std::vector<int> a = { 5, 4, 3, 2, 1 };
  return 0;
=======
const int Mod = 998244353;

int solve(int H, int W, char S[][W_MAX + 2])
{
	int i, j, rect_sum[H_MAX + 2][W_MAX + 2];
	for (j = 0; j <= W; j++) rect_sum[0][j] = 0;
	for (i = 1; i <= H; i++) {
		rect_sum[i][0] = 0;
		for (j = 1; j <= W; j++) {
			rect_sum[i][j] = rect_sum[i-1][j] + rect_sum[i][j-1] - rect_sum[i-1][j-1] + ((S[i][j] == 'Y')? 1: 0);
		}
	}
	if (rect_sum[H][W] % 2 != 0) return 0;
	
	int h, w, y = rect_sum[H][W] / 2, k, l, h_fence[H_MAX + 2], w_fence[W_MAX + 2], next_sum;
	long long ans = 0, deg_free;
	for (h = 0; h < H; h++) {
		if (y % (h + 1) != 0) continue;
		w = y / (h + 1) - 1;
		if (w < 0 || w >= W) continue;
		
		deg_free = 1;
		for (i = 1, k = 0, h_fence[0] = 0, next_sum = (w + 1) * 2; k < h; i++) {
			if (rect_sum[i][W] > next_sum) break;
			else if (rect_sum[i][W] == next_sum) {
				h_fence[++k] = i;
				next_sum += (w + 1) * 2;
				
				for (i++, l = 1; rect_sum[i][W] == rect_sum[i-1][W]; i++, l++);
				deg_free = deg_free * l % Mod;
				i--;
			}
		}
		if (k < h) continue;
		h_fence[h+1] = H;
		
		for (j = 1, k = 0, w_fence[0] = 0, next_sum = (h + 1) * 2; k < w; j++) {
			if (rect_sum[H][j] > next_sum) break;
			else if (rect_sum[H][j] == next_sum) {
				w_fence[++k] = j;
				next_sum += (h + 1) * 2;

				for (j++, l = 1; rect_sum[H][j] == rect_sum[H][j-1]; j++, l++);
				deg_free = deg_free * l % Mod;
				j--;
			}
		}
		if (k < w) continue;
		w_fence[w+1] = W;
		
		for (i = 1; i <= h + 1; i++) {
			for (j = 1; j <= w + 1; j++) {
				if (rect_sum[h_fence[i]][w_fence[j]] - rect_sum[h_fence[i-1]][w_fence[j]] - rect_sum[h_fence[i]][w_fence[j-1]] + rect_sum[h_fence[i-1]][w_fence[j-1]] != 2) break;
			}
			if (j <= w + 1) break;
		}
		if (i <= h + 1) continue;
		
		ans += deg_free;
	}
	return ans % Mod;
}

int main()
{
	int i, H, W;
	char S[H_MAX + 2][W_MAX + 2] = {};
	scanf("%d %d", &H, &W);
	for (i = 1; i <= H; i++) scanf("%s", &(S[i][1]));
	printf("%d\n", solve(H, W, S));
	fflush(stdout);
	return 0;
>>>>>>> Stashed changes
}