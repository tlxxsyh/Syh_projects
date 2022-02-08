#include <iostream>
#pragma once

using namespace std;

class Stone
{
private:
	int m;//总石头数
	int n;//每次最多拿的个数
	int first;//先后手标记，1为玩家先手，2为玩家后手
	int tem;//玩家选择拿的个数
	int isend = 1;//判断游戏是否结束
public:
	void rules();
	void reset();
	void set_m();
	void set_n();
	void set_first();
	void predict();
	void start();
	void computer();
	void player();
	void judge_c();
	void judge_p();
};

//介绍规则函数
void Stone::rules() {
	cout << "游戏规则：\n总共有m个石子，两个人轮流拿1~n个石子，拿到最后一个石子者获胜！\n\n";
}

//初始化设定函数
void Stone::reset() {
	isend = 1; 
	cout << "机器人：你好，我是拿石头智能机器人！" << endl;
	set_m();
	set_n();
	set_first();
}

//设定m
void Stone::set_m() {
	cout << "\n机器人：请输入总共的小石头数m：";
	cin >> m;
	while (m<1) {
		cout << "机器人：总石头数应当大于0！请重新输入：";
		cin >> m;
	}
}

//设定n
void Stone::set_n() {
	cout << "\n机器人：请规定每次能拿的最大个数：";
	cin >> n;
	while (n <= 0 || n > m) {
		cout << "机器人：输入数据应当是介于1~m之间的任意整数！请重新输入：";
		cin >> n;
	}
}

//设定先后手
void Stone::set_first() {
	cout << "\n机器人：你想要先手还是后手呢（1表示先手，2表示后手）:";
	cin >> first;
	while (first != 1 && first != 2) {
		cout << "机器人：输入数据应当是1或2！请重新输入：";
		cin >> first;
	}
}

void Stone::predict() {
	//后手胜的情况
	if (m % (n + 1) == 0) {
		//玩家先手
		if (first == 1) {
			cout << "\n机器人：那你一定会输" << endl << endl;
		}
		else {
			cout << "\n机器人：我不一定能赢你" << endl << endl;
		}
	}
	//先手胜的情况
	else { 
		//玩家先手
		if (first == 1) {
			cout << "\n机器人：我不一定能赢你" << endl << endl;
		}
		else {
			cout << "\n机器人：那你一定会输" << endl << endl;
		}
	}
}

//游戏主函数
void Stone::start() {
	//机器人先手的情况下，机器人先进行一步
	if (first == 2) {
		computer();
	}
	//循环进行游戏
	while (isend) {
		judge_c();
		if (isend == 0) {
			break;
		}
		player();
		judge_p();
		if (isend == 0) {
			break;
		}
		computer();
	}
}

//机器人拿石头
void Stone::computer() {
	int goodNum = 1;
	goodNum = m % (n + 1);
	if (goodNum == 0) {
		goodNum = 1;
	}
	m = m - goodNum;
	cout << "机器人：我拿" << goodNum << "个，此时还剩" << m << "个" << endl;
}

//玩家拿石头
void Stone::player() {
	cout << "我：我拿个数：";
	cin >> tem;
	while (tem<1 || tem>n || tem > m) {
		cout << "我：拿的不太对哎....我到底拿几个呢：";
		cin >> tem;
	}
	m = m - tem;
	cout << "此时还剩下" << m << "个。" << endl << endl;
}

//判断电脑是否胜利
void Stone::judge_c() {
	if (m == 0) {
		cout << "机器人：我赢了！\n\n";
		cout << "=======游戏结束======="<<endl;
		isend = 0;
		cout << "按下任意键重新开始...";
		getchar(); getchar();
		system("cls");
	}
}

//判断玩家是否胜利
void Stone::judge_p() {
	if (m == 0) {
		cout << "机器人：你赢了！\n\n";
		cout << "=======游戏结束======="<<endl;
		isend = 0;
		cout << "按下任意键重新开始...";
		getchar(); getchar();
		system("cls");
	}
}
