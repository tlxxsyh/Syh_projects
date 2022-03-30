/**
*输入一个数字n(n<500)
*会自动输出一个n阶幻方(横、竖、斜的和都相同)
*/
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	int n, n2, magic[500][500] = { 0 }, x, y, num;
	cin >> n;
	n2 = n * n;//n2是幻方的数字个数
	x = n / 2 + 1;
	y = 1;
	num = 1;
	magic[y][x] = num;
	n2 = n2 - 1;//因为已经填了一个数
	while (n2--) {
		if (y == 1 && x != n) {
			y = n; x = x + 1;
			magic[y][x] = ++num;
		}
		else if (y != 1 && x == n) {
			y = y - 1; x = 1;
			magic[y][x] = ++num;
		}
		else if (y == 1 && x == n) {
			y = y + 1;
			magic[y][x] = ++num;
		}
		else if (y != 1 && x != n) {
			if (magic[y - 1][x + 1] == 0) {
				magic[y - 1][x + 1] = ++num;
				y = y - 1;
				x = x + 1;
			}
			else {
				magic[y + 1][x] = ++num;
				y = y + 1;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << magic[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
