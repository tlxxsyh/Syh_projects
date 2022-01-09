#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstdlib>
#include <easyx.h>

using namespace std;

class Game 
{
private:
	int map[5][5];
	int rows[5][5];
	int lines[5][5];
public:
	int key;
	Game(){
		//初始化
		memset(map, 0, sizeof(map));
		memset(map, 0, sizeof(rows));
		memset(map, 0, sizeof(lines));
		key = 0;
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
};

int main()
{      
	srand(time(NULL));     //随机种子
	Game game2048;         //实例化游戏
	game2048.showMap();    //展示棋盘
	//游戏过程
	while (1)
	{
		game2048.key = game2048.keyEvent();
		game2048.move();
		game2048.initNum();
		system("cls");
		game2048.showMap();
	}
	return 0;
}
//移动操作
void Game::move()
{
	//首先二维数组转为一维数组
	this->getArray();
	//上下移动的情况
	if (this->key == 72 || this->key == 80)
	{
		for (int i = 1; i <= 4; i++){
			this->left(lines[i]);
		}
		//一维数组转成二维数组
		this->getMapLine();
	}
	//左右移动的情况
	else
	{
		for (int i = 1; i <= 4; i++){
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
	//若是满了则无法插入，因此需要检测一下是否满
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (map[i][j] != 0)
			{
				cnt++;
			}
		}
	}	
	//如果满了，则跳出循环
	if (cnt == 16)
	{
		break;
	}
}

//创建随机数2、4
int Game::creatNumber()
{
	if (rand() % 3 == 1){
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
			if (key == 75 || key == 80 || key == 72 || key == 77){
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
				lines[i][j] = this->map[4-j+1][i];
			}
		}
	}
	//左
	else if (this->key== 75)
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
				rows[i][j] = this->map[i][4-j+1];
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
				map[j][i] = lines[i][4-j+1];
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
				map[i][j] = rows[i][4-j+1];
			}
		}
	}
}
