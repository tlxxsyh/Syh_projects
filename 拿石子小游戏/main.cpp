#include "Stone.h"
#include <iostream>
#include "Stone.h"

using namespace std;

int main()
{
	//页面初始化
	system("title 拿石子小游戏智能机器人v1.0");
	system("mode con cols=85 lines=30");
	//system("color F0");
	//创建游戏
	Stone game;
	while (true) {
		game.rules();
		game.reset();
		game.predict();
		game.start();
	}
	return 0;
}
