#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
#include <string>
using namespace std;

int main()
{
	system("title 欢迎使用进程自动结束工具 @Shang Yuhang");
	//读取进程表
	ifstream ifs;
	ifs.open("D:/Kill_List.txt", ios::in);
	//如果第一次使用则初始化
	if (!ifs.is_open())
	{
		//如果没有进程表，则创建
		ofstream ofs;
		ofs.open("D:/Kill_List.txt", ios::out | ios::app);
		cout << "系统判断您是第一次使用本程序" << endl;
		Sleep(1500);
		cout << "下面是简单的帮助教程：" << endl << endl;
		Sleep(1500);
		cout << "您可以在D盘根目录中找到 Kill_List.txt 文件" << endl;
		Sleep(1500);
		cout << "然后在每一行写下您关机时想要自动关闭的进程名称即可" << endl;
		Sleep(1500);
		cout << "您的写法例如：QQ.exe" << endl;
		Sleep(1500);
		cout << "但是请注意，每个进程都需占一行" << endl;
		Sleep(1500);
		cout << "按下任意键结束..." << endl;
		getchar();
		ofs.close();
	}
	//删除进程的操作
	else
	{
		char process[1024];
		while (ifs.getline(process,1024))
		{
			//删除操作字符串
			char cmd[1024]= "taskkill /f /im ";
			strcat(cmd, process);
			system(cmd);
		}
	}
	ifs.close();
	return 0;
}
