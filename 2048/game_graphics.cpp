/**
*   @title:2048游戏（图形化）
*   @Lisence:All rights(转载请说明出处)
*/

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstdlib>
#include <easyx.h>
#include <math.h>

using namespace std;

#define GRID_WIDTH 100 //每个方格宽
#define EDGE 15        //缝隙宽度

//每个方格的颜色
enum Color
{
	color0 = RGB(205, 193, 180),
	color2 = RGB(238, 228, 218),
	color4 = RGB(237, 224, 200),
	color8 = RGB(242, 177, 121),
	color16 = RGB(245, 149, 99),
	color32 = RGB(246, 124, 95),
	color64 = RGB(246, 94, 59),
	color128 = RGB(237, 207, 114),
	color256 = RGB(237, 204, 97),
	color512 = RGB(140, 222, 246),
	color1024 = RGB(38, 73, 136),
	color2048 = RGB(211, 141, 177),
	colorBG = RGB(187, 173, 160),
};
Color colors[13] = { color0,color2, color4, color8, color16, color32, color64,color128,color256,color512,color1024,color2048,colorBG };

//2048类
class Game
{
	friend void drawGrid(Game* game2048);
	friend void showScore(Game* game2048);
private:
	int map[5][5];
	int rows[5][5];
	int lines[5][5];
	int score;
	int best_score;
public:
	int key;
	Game() {
		//初始化
		memset(map, 0, sizeof(map));
		memset(map, 0, sizeof(rows));
		memset(map, 0, sizeof(lines));
		key = 0;
		score = 0;
		best_score = 0;
		initNum();
		initNum();
	}
	void showMap();//展示棋盘
	void initNum();//插入随机数
	int keyEvent();//获取按键
	void getArray();//获取一维数组
	void move();//移动操作
	void getMapLine();//数组还原
	void getMapRow();//数组还原
	void left(int a[]);//左移
	int creatNumber();//创造随机数2或4
	int getMap(int x, int y);//获取棋盘数字

};

void drawGrid(Game* game2048);       //绘制格子
void showScore(Game* game2048);      //显示头部

int main()
{
	srand(time(NULL));     //随机种子
	Game game2048;         //实例化游戏
	game2048.showMap();    //展示棋盘
	//创建图形窗口
	initgraph(4 * GRID_WIDTH + 5 * EDGE, 675);
	//设置背景颜色
	setbkcolor(RGB(250, 248, 239));
	cleardevice();//清屏（同步）
	//设置背景模式为透明
	setbkmode(TRANSPARENT);

	//游戏过程
	while (1)
	{
		showScore(&game2048);
		//绘制格子
		drawGrid(&game2048);
		//获取按键
		game2048.key = game2048.keyEvent();
		//操作移动
		game2048.move();
		//创造新格子
		game2048.initNum();

		//控制台输出
		system("cls");
		game2048.showMap();
	}
	return 0;
}

//展示分数
void showScore(Game* game2048)
{
	//程序标题
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 125;						// 设置字体高度为 125
	_tcscpy(f.lfFaceName, _T("汉仪游园体W"));// 设置字体为“汉仪游园体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿
	settextstyle(&f);						// 设置字体样式
	settextcolor(BLACK);
	outtextxy(25, 25, "2048");

	//游戏区块
	{
		setfillcolor(RGB(187, 173, 160));
		solidroundrect(5, 200, 470, 670, 10, 10);
	}

	//当前成绩
	f.lfHeight = 35;
	settextstyle(&f);
	outtextxy(25, 150, "score:");
	//score
	int start_score = textwidth("score:") + 30;
	char prt_score[10] = { 0 };
	sprintf(prt_score, "%d", game2048->score);
	//因为每次成绩采用覆盖上次成绩的方法，故延长一段空白，防止上面的字符比下面的字符短
	strcat(prt_score, "    ");
	setbkmode(OPAQUE);
	outtextxy(start_score, 150, prt_score);
	setbkmode(TRANSPARENT);
}

//绘制格子
void drawGrid(Game* game2048)
{
	//i是行，j是列
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			//x,y位置
			int x = j * EDGE + (j - 1) * GRID_WIDTH;
			int y = 200 + i * EDGE + (i - 1) * GRID_WIDTH;

			//设置填充色
			if (game2048->map[i][j]) {
				int color_index = log2(game2048->map[i][j]);
				setfillcolor(colors[color_index]);
			}
			else {
				setfillcolor(colors[0]);
			}

			//绘制16个格子
			solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);
			if (game2048->map[i][j] != 0)
			{
				//设置字体大小
				settextstyle(50, 0, "微软雅黑");
				//获取文字
				char str[5] = { 0 };
				sprintf(str, "%d", game2048->map[i][j]);
				//水平间隔、上下间隔
				int widd = (GRID_WIDTH - textwidth(str)) / 2;
				int higt = (GRID_WIDTH - textheight(str)) / 2;

				//设置内容
				outtextxy(x + widd, y + higt, str);
			}

		}

	}
}

//移动操作
void Game::move()
{
	//首先二维数组转为一维数组
	this->getArray();
	//上下移动的情况
	if (this->key == 72 || this->key == 80)
	{
		for (int i = 1; i <= 4; i++) {
			this->left(lines[i]);
		}
		//一维数组转成二维数组
		this->getMapLine();
	}
	//左右移动的情况
	else
	{
		for (int i = 1; i <= 4; i++) {
			this->left(rows[i]);
		}
		this->getMapRow();
	}
}

//数组左移
void Game::left(int a[])
{
	//看能否相加的遍历
	for (int i = 1; i < 4; i++) {
		//如果此位置不为0
		if (a[i] != 0)
		{
			//寻找下一个不为0的位置，看能否相加
			for (int j = i + 1; j <= 4; j++)
			{
				//如果不为0，看是否相等
				if (a[j] != 0)
				{
					//如果相等
					if (a[i] == a[j])
					{
						a[i] = 2 * a[i];
						a[j] = 0;
						score += 2 * a[i];
					}
					//如果不等，则什么都不做
					//要跳出寻找不为0的数的循环
					break;
				}
				//为0，则什么都不做
			}
		}
		//如果此位置为0，则什么都不做
	}
	//移动的遍历(需要检查3次）
	for (int q = 1; q <= 3; q++)
	{
		for (int i = 3; i >= 1; i--)
		{
			if (a[i] == 0)
			{
				a[i] = a[i + 1];
				a[i + 1] = 0;
			}
		}
	}
}

//显示棋盘
void Game::showMap()
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			cout << map[i][j] << "\t";
		}
		cout << "\n";
	}
}

//随机插入
void Game::initNum()
{
	int x, y;
	//随机创建坐标
	while (1)
	{
		x = rand() % 4 + 1;
		y = rand() % 4 + 1;
		if (map[x][y] == 0) {
			map[x][y] = creatNumber();
			break;
		}
	}
}

//创建随机数2、4
int Game::creatNumber()
{
	if (rand() % 3 == 1) {
		return 4;
	}
	return 2;
}

//获取按键
int Game::keyEvent()
{
	int key;
	while (1) {
		key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == 75 || key == 80 || key == 72 || key == 77) {
				break;
			}
		}
	}
	return key;
}

//二维转一维
void Game::getArray()
{
	//上
	if (this->key == 72)
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				lines[i][j] = this->map[j][i];
			}
		}
	}
	//下
	else if (this->key == 80)
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				lines[i][j] = this->map[4 - j + 1][i];
			}
		}
	}
	//左
	else if (this->key == 75)
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				rows[i][j] = this->map[i][j];
			}
		}
	}
	//右
	else if (this->key == 77)
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				rows[i][j] = this->map[i][4 - j + 1];
			}
		}
	}
}

//列转图
void Game::getMapLine()
{
	if (key == 72)
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				map[j][i] = lines[i][j];
			}
		}
	}
	else
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				map[j][i] = lines[i][4 - j + 1];
			}
		}
	}

}

//行转图
void Game::getMapRow()
{
	if (key == 75)
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				map[i][j] = rows[i][j];
			}
		}
	}
	else
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				map[i][j] = rows[i][4 - j + 1];
			}
		}
	}
}

//获取棋盘数字
int Game::getMap(int x, int y)
{
	return map[x][y];
}
