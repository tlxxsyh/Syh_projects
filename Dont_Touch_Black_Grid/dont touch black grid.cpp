#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <easyx.h>
#include <math.h>
#include <string.h>
using namespace std;

float gravity = 0.5;                     //重力加速度
int score = 0;                           //分数
//定义屏幕大小
float window_width, window_height;


//球类
class my_ball
{
public:
	float x, y, radius, vy;
	my_ball() {
		radius = 20;                        //半径为20
		x = window_width / 4;               //x坐标 在屏幕四分之一处
		y = window_height - radius;    //y坐标 在屏幕底部
		vy = 0;                             //初速度为0
	}
	void jump();
	void move();
};
//方块类
class my_rectangle
{
public:
	float height, width, left, vx;
	my_rectangle() {
		width = 20;
		height = 100;
		left = 400;
		vx = -3;
	}
	void move();
};
//跳跃按键捕捉
void jump();

int main()
{
	//设置窗口大小
	window_width = 600;
	window_height = 400;
	//创建小球对象
	my_ball ball_example;
	//创建方块对象
	my_rectangle rectangle_example;

	//创建屏幕
	initgraph(window_width, window_height);
	setbkcolor(WHITE);

	//游戏
	while (1)
	{
		//捕获跳跃的函数
		ball_example.jump();
		//小球维持自由落体运动函数
		ball_example.move();
		//方块运动函数
		rectangle_example.move();
		
		//碰撞判断
		//当高度小于方块
		if (rectangle_example.left <= ball_example.x + ball_example.radius &&
			ball_example.y + ball_example.radius >= window_height - rectangle_example.height &&
			ball_example.x - ball_example.radius <= rectangle_example.left + rectangle_example.width)
		{
			score = 0;
			Sleep(100);
		}

		//清屏
		cleardevice();
		
		//绘制小球
		setfillcolor(BLUE);
		fillcircle(ball_example.x, ball_example.y, ball_example.radius);
		//绘制方块
		setfillcolor(BLACK);
		fillrectangle(rectangle_example.left,window_height-rectangle_example.height,rectangle_example.left+rectangle_example.width,window_height);
		
		//显示速度
		settextcolor(BLACK);
		settextstyle(50, 0, "汉仪游园体W");
		outtextxy(10, 10, "分数：");
		char str[10];
		sprintf(str, "%d",score);
		outtextxy(120, 10, str);
		
		//延时
		Sleep(10);
	}
	return 0;
}

void my_ball::jump()
{
	if (kbhit())//按空格跳跃
	{
		char input = _getch();
		if (input == ' ' && y >= window_height - radius - 10)
		{
			vy = -15;
		}
	}
}
void my_ball::move()
{
	//一定要先算速度，再算位置
		//小球位置
	vy = vy + gravity;
	y = y + vy;
	//防止小球往下穿越
	if (y >= window_height - radius)
	{
		y = window_height - radius;
	}
}

void my_rectangle::move()
{
	//方块位置
	left = left + vx;
	//使方块循环出现
	if (left < 0)
	{
		left = window_width;
		score++;
		height = rand() % int(window_height / 4) + window_height / 5;
		vx = rand() / float(RAND_MAX) * 4 - 7;
	}
}
