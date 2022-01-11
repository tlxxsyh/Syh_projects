#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <easyx.h>
#include <math.h>
#include <string.h>

#define GRID_SIZE 20
#define GRID_H_NUM 40
#define GRID_W_NUM 40

using namespace std;

class Snake
{
private:
	int map[GRID_H_NUM][GRID_W_NUM];
	int food_x, food_y;                   //随机食物位置
public:

	//构造函数
	Snake() {
		memset(map, 0, sizeof(map));
		for (int i = 1; i <= 5; i++)
		{
			map[GRID_H_NUM / 2][GRID_W_NUM / 2 - i + 1] = i;
		}
		//修改行边框
		for (int i = 0; i < GRID_W_NUM; i++)
		{
			map[0][i] = -1;
			map[GRID_H_NUM - 1][i] = -1;
		}
		//修改列边框
		for (int j = 0; j < GRID_H_NUM; j++)
		{
			map[j][0] = -1;
			map[j][GRID_W_NUM - 1] = -1;
		}
		//初始化食物
		food_x = rand() % (GRID_H_NUM - 5) + 2;
		food_y = rand() % (GRID_W_NUM - 5) + 2;
		map[food_x][food_y] = -2;
	}
	void draw();           //绘制蛇
	void getKey();         //按键更新移动
	void autoMove();        //自动移动（防止按键延迟）
	void move();           //移动
};

//int Map[GRID_H_NUM][GRID_W_NUM];

int Key =77;                          //移动方向状态
int score=0;                          //记录蛇的长度
void DrawMap();                       //绘制底图
int main()
{
	DrawMap();
	Snake snake;
	snake.draw();
	while (1)
	{
		snake.draw();
		snake.autoMove();
		snake.getKey();
		
		Sleep(100);	
	}
	return 0;
}

//绘制地图
void DrawMap()
{
	initgraph(GRID_W_NUM * GRID_SIZE+310, GRID_H_NUM * GRID_SIZE);
	setbkcolor(RGB(247, 246, 242));
	cleardevice();
	//贪吃蛇标题
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 100;						// 设置字体高度为 125
	_tcscpy(f.lfFaceName, _T("汉仪游园体W"));// 设置字体为“汉仪游园体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿
	settextstyle(&f);						// 设置字体样式
	settextcolor(BLACK);
	outtextxy(GRID_W_NUM * GRID_SIZE + 35,30, "贪吃蛇");
	//成绩
	f.lfHeight = 50;
	_tcscpy(f.lfFaceName, _T("Segoe Print"));
	settextstyle(&f);
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 150, "SCORE：");
	//游戏介绍
	f.lfHeight = 30;
	_tcscpy(f.lfFaceName, _T("迷你简卡通"));
	settextstyle(&f);
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 250, "游戏介绍：");
	f.lfHeight = 24;
	settextstyle(&f);
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 290, "1976年，Gremlin平台推出了");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 320, "一款经典街机游戏Blockade。");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 350, "游戏中，玩家只能控制角色向");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 380, "左、右方向90度转弯，玩家要");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 410, "做的就是避免撞上障碍物和越");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 440, "来越长的身体。");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 470, "Blockade很受欢迎，但真正");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 500, "让这种游戏形式红遍全球的还");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 530, "是21年后随诺基亚手机走向世");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 560, "世界的贪吃蛇游戏——Snake");
	//操作方法
	f.lfHeight = 30;
	settextstyle(&f);
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 600, "操作方法：");
	f.lfHeight = 24;
	settextstyle(&f);
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 640, "通过↑↓←→键控制蛇的移动");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 670, "按下空格键暂停");
	outtextxy(GRID_W_NUM * GRID_SIZE + 25, 700, "尽可能多的吃掉蓝色方块叭！");
	
	//欢迎访问
	f.lfHeight = 30;
	_tcscpy(f.lfFaceName, _T("Bradley Hand ITC"));
	settextstyle(&f);
	outtextxy(GRID_W_NUM * GRID_SIZE + 40, 755, "Author:Shang Yuhang");

}
//绘制蛇
void Snake::draw()
{
	int i, j;
	setlinecolor(RGB(225, 224, 220));
	for (i = 0; i < GRID_H_NUM; i++)
	{
		for (j = 0; j < GRID_W_NUM; j++)
		{
			//蛇身
			if (map[i][j] > 0)
				setfillcolor(HSVtoRGB(map[i][j] * 10, 0.9, 1));
			//边框
			else if (map[i][j] == -1)
				setfillcolor(RGB(151, 150, 151));
			//食物
			else if (map[i][j] == -2)
				setfillcolor(RGB(117, 206, 249));
			//背景
			else
				setfillcolor(RGB(247, 246, 242));
			fillrectangle(j * GRID_SIZE, i * GRID_SIZE, (j + 1) * GRID_SIZE, (i + 1) * GRID_SIZE);
		}
	}
}
//获取按键,上72，下80，左75，右77
void Snake::getKey()
{
	int tkey;
	if (kbhit())
	{
		tkey = _getch();
		if (tkey == 224)//方向键
		{
			tkey = _getch();
			//注意Key与tkey不同
			//临时变量是为了保证向上下移动状态下只能接受左右命令
			if (Key == 72||Key==80) {
				if (tkey == 75 || tkey == 77)
					Key = tkey;
				else;
			}
			else if(Key==75||Key==77){
				if (tkey == 72 || tkey == 80)
					Key = tkey;
				else;
			}
		}
		else if (tkey == 32)//空格键
		{
			system("pause");
		}
	}
	move();
}
//蛇的移动
void Snake::move()
{
	int old_head_x;
	int old_head_y;
	int tail_x;
	int tail_y;
	int max_num = 0;
	
	//全部数字加一
	for (int i = 1; i < GRID_H_NUM-1; i++)
		for (int j = 1; j < GRID_W_NUM-1; j++)
			if (map[i][j] > 0)
				map[i][j]++;
	//寻找头部与尾部
	for (int i = 1; i < GRID_H_NUM-1; i++)
	{
		for (int j = 1; j < GRID_W_NUM-1; j++)
		{
			if (map[i][j] > max_num)
			{
				max_num = map[i][j];
				tail_x = i;
				tail_y = j;
			}
			if (map[i][j] == 2)
			{
				old_head_x = i;
				old_head_y = j;
			}
		}
	}
	int new_head_x,new_head_y;
	//头部置一
	if (Key == 77)//右
	{
		new_head_x = old_head_x;
		new_head_y = old_head_y + 1;
	}
	if (Key == 72)//上
	{
		new_head_x = old_head_x-1;
		new_head_y = old_head_y;
	}
	if (Key == 80)//下
	{
		new_head_x = old_head_x+1;
		new_head_y = old_head_y;
	}
	if (Key == 75)//左
	{
		new_head_x = old_head_x;
		new_head_y = old_head_y - 1;
	}

	// 新蛇头如果吃到食物
	if (map[new_head_x][new_head_y] == -2)
	{
		score++;
		//删去当前食物
		map[food_x][food_y] = 0;
		// 产生一个新的食物
		food_x = rand() % (GRID_H_NUM - 5) + 2;
		food_y = rand() % (GRID_W_NUM - 5) + 2;
		map[food_x][food_y] = -2;

		// 原来的旧蛇尾留着，长度自动+1

		//显示成绩
		clearrectangle(GRID_W_NUM * GRID_SIZE + 160, 150, GRID_W_NUM * GRID_SIZE + 260,210);
		setbkmode(TRANSPARENT);
		LOGFONT fff;
		gettextstyle(&fff);						// 获取当前字体设置
		fff.lfHeight = 50;						// 设置字体高度为 50
		_tcscpy(fff.lfFaceName, _T("汉仪昌黎宋刻本(精修版)W"));// 设置字体为“汉仪游园体”(高版本 VC 推荐使用 _tcscpy_s 函数)
		fff.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿
		settextstyle(&fff);						// 设置字体样式
		settextcolor(BLACK);
		char str[10];
		sprintf(str, "%d", score);
		outtextxy(GRID_W_NUM * GRID_SIZE + 160, 150, str);
	}
	else // 否则，原来的旧蛇尾减掉，保持长度不变
	{
		map[tail_x][tail_y] = 0;
	}

	//判断是否撞到自身或者边框
	if (map[new_head_x][new_head_y] > 0 || map[new_head_x][new_head_y] == -1)
	{
		//游戏结束
		setbkmode(TRANSPARENT);
		LOGFONT ff;
		gettextstyle(&ff);						// 获取当前字体设置
		ff.lfHeight = 150;						// 设置字体高度为 125
		_tcscpy(ff.lfFaceName, _T("汉仪昌黎宋刻本(精修版)W"));// 设置字体为“汉仪游园体”(高版本 VC 推荐使用 _tcscpy_s 函数)
		ff.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿
		settextstyle(&ff);						// 设置字体样式
		settextcolor(RED);
		outtextxy(180, 280, "游戏结束");
		//等待两秒
		Sleep(2000);
		ff.lfHeight = 50;
		settextstyle(&ff);
		outtextxy(235, 430, "按下任意键结束游戏");
		system("pause");
		exit(0);
	}
	else//没撞到则更新蛇头
		map[new_head_x][new_head_y] = 1;
}
//蛇的自动移动（防止按键延迟）
void Snake::autoMove()
{
	static int waitIndex = 1;
	waitIndex++;
	if (waitIndex == 10)
	{
		move();
		waitIndex = 1;
	}
}

