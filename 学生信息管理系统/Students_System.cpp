//============================================================================
// Name        : Students_System
// Author      : Yuhang_Shang
// Date        : 2021.9.21
// Copyright   : all rights reserved
// Github      : https://github.com/tlxxsyh
// Description : 本代码为C++代码
//               实现一个美观的学生信息管理系统
//               具有基本的增删改查功能
//               并且每次清屏，显示菜单，防止程序显示过长以致翻阅不便
//============================================================================

#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;

//全局变量在此声明

//学生信息结构体
struct form
{
    string id;     //学号
    string name;   //姓名
    int sex;       //性别
    int sumscore;  //总分
    int score[20]; //各科成绩数组
} student[10000];

int CntStudent = 0;       //学生总数
int index;                //i用来计学生数
int All_score = 0;        //统计所有学生总分
double Avg_All_Score = 0; //统计所有学生均分

void Menu(void);                                   //显示菜单
void AppendRecord(void);                           //输入成绩
int ListRecord(void);                              //列出成绩
void DeletRecord(struct form *student);            //删除成绩
void ModifyRecord(struct form *student);           //修改成绩
void SearchRecord(struct form *student);           //查询某个人成绩
void MySort(struct form *student);                 //调出排序函数界面
bool Descending_sum(struct form a, struct form b); //总分降序排序函数
bool Ascending_sum(struct form a, struct form b);  //总分升序排序函数
bool Descending_num(struct form a, struct form b); //学号降序排序函数
bool Ascending_num(struct form a, struct form b);  //学号升序排序函数
void WriteFile(struct form *student);              //写文件

int main()
{
    //此处定义命令变量
    char command;
    //输出菜单
    Menu();
    //输入命令
    while (1)
    {
        cin >> command;
        //命令执行
        if (command == '1') //添加学生信息
        {
            AppendRecord();
        }
        else if (command == '2') //列出学生信息
        {
            ListRecord();
        }
        else if (command == '3') //删除学生信息
        {
            DeletRecord(student);
        }
        else if (command == '4') //修改学生信息
        {
            ModifyRecord(student);
        }
        else if (command == '5') //搜索学生信息
        {
            SearchRecord(student);
        }
        else if (command == '6') //总分降序排序
        {
            MySort(student);
            sort(student + 1, student + CntStudent + 1, Descending_sum);
        }
        else if (command == '7') //总分升序排序
        {
            MySort(student);
            sort(student + 1, student + CntStudent + 1, Ascending_sum);
        }
        else if (command == '8') //学号降序排序
        {
            MySort(student);
            sort(student + 1, student + CntStudent + 1, Descending_num);
        }
        else if (command == '9') //学号升序排序
        {
            MySort(student);
            sort(student + 1, student + CntStudent + 1, Ascending_num);
        }
        else if (command == 'W') //写文件
        {
            WriteFile(student);
            cout << "写入成功！";
        }
        else if (command == 'R') //读文件
        {
        }
        else if (command == '0') //退出
        {
            return 0;
        }
    }
    return 0;
}

//显示菜单
void Menu(void)
{
    cout << "=========================================\n";
    cout << "Management for Students' scores\n";
    cout << "1.Append record\n";
    cout << "2.List record\n";
    cout << "3.Delet record\n";
    cout << "4.Modify record\n";
    cout << "5.Search record\n";
    cout << "6.Sort in descending order by sum\n";
    cout << "7.Sort in ascending order by sum\n";
    cout << "8.Sort in descending order by num\n";
    cout << "9.Sort in ascending order by num\n";
    cout << "W.Write to a file\n";
    cout << "R.Read from a File\n";
    cout << "0.Exit\n";
    cout << "=========================================\n\n";
    cout << "Please input your choice：";
}

//添加学生信息
void AppendRecord(void)
{
    index = CntStudent + 1; //本次学生的位置在总数加1的位置上
    system("cls");
    cout << "*****************************************************************\n";
    cout << "*\t提示：请输入学生姓名，性别（0表示女，1表示男），学号\t*\n";
    cout << "*****************************************************************\n\n";
    //循环输入学生信息
    for (;; index++)
    {
        cout << "开始录入第" << index << "个学生信息" << endl;
        cin >> student[index].name >> student[index].sex >> student[index].id;
        cout << "请依次输入" << student[index].name << "的5门科目分数\n";
        int j = 1;
        for (; j <= 5; j++)
        {
            cin >> student[index].score[j];
            student[index].sumscore += student[index].score[j];
        }
        All_score += student[index].sumscore; //所有学生总分增加

        char y_or_n;
        cout << "录入信息成功，是否继续录入学生信息（y/n):";
        cin >> y_or_n;
        if (y_or_n == 'n')
        {
            system("cls"); //清屏
            Menu();
            break;
        }
    }
    //记录学生数据个数
    CntStudent = index;
}

//列出学生信息
int ListRecord(void) //列出成绩
{
    int i = 1, j = 1;
    system("cls");
    cout << "*************************\n";
    cout << "*\t学生信息表\t*\n";
    cout << "*************************\n\n";
    cout << "-------------------------\n";
    if (CntStudent == 0)
    {
        cout << "目前无学生信息\n";
        cout << "输入menu以继续\n"
             << endl;
        string continuee;
        cin >> continuee;
        if (continuee == "menu")
        {
            system("cls");
            Menu();
            return 0;
        }
    }
    //输出所有学生信息
    for (i = 1; i <= CntStudent; i++)
    {
        cout << student[i].name;
        if (student[i].sex == 1)
            cout << " 男 ";
        else
            cout << " 女 ";
        cout << student[i].id << endl;
        cout << "该生各科分数：";
        for (j = 1; j <= 5; j++)
        {
            cout << student[i].score[j] << " ";
        }
        cout << "\n";
        cout << "该生总分：" << student[i].sumscore << endl;
        cout << "-------------------------\n";
    }
    //输出均分
    Avg_All_Score = (double)All_score / CntStudent;
    cout << "\n平均分：" << Avg_All_Score << "\n";
    //输出当前总人数
    cout << "当前总人数为：" << CntStudent << endl;
    //输出menu以继续
    cout << "输入menu以继续\n"
         << endl;
    string continuee;
    cin >> continuee;
    if (continuee == "menu")
    {
        system("cls");
        Menu();
    }
    return 0;
}

//删除学生信息
void DeletRecord(struct form *student)
{
    int i = 1, j, k, isbreak = 0;
    string id;
    system("cls");
    cout << "请输入你要删除的学号，输入menu返回菜单\n";
    while (1)
    {
        isbreak = 0;
        cin >> id;
        if (id == "menu") //中止输入的情况
        {
            system("cls");
            Menu();
            break;
        }
        for (i = 1; i <= CntStudent; i++)
        {
            if (student[i].id == id)
            {
                //cout<<"找到此生在"<<i<<"位置！\n";
                All_score -= student[i].sumscore; //学生总分减少此生分数
                for (j = i; j < CntStudent; j++)  //顺次往前移动一位（删除该生）
                {
                    student[j].id = student[j + 1].id;
                    student[j].name = student[j + 1].name;
                    student[j].sex = student[j + 1].sex;
                    student[j].sumscore = student[j + 1].sumscore;
                    for (k = 1; k <= 5; k++) //五门课的替换
                    {
                        student[j].score[k] = student[j + 1].score[k];
                    }
                }
                CntStudent--;
                cout << "删除成功！是否要继续删除学生数据（y/n):";
                char y_or_n;
                cin >> y_or_n;
                if (y_or_n == 'n')
                {
                    system("cls");
                    Menu();
                    isbreak = 1;
                    break;
                }
                else
                {
                    isbreak = 2;
                    cout << "请输入学号：" << endl;
                    break;
                }
            }
        }
        if (isbreak == 1)
            break;
        if (isbreak == 0)
            cout << "未找到该生，请重新输入所需删除的学号，输入menu返回\n";
    }
}

//修改学生信息
void ModifyRecord(struct form *student) //修改成绩
{
    system("cls");
    string id;
    int modify, isfind = 0, i; //修改的项目,是否找到
    while (1)
    {
        isfind = 0;
        cout << "请输入该生学号，输入menu返回菜单：" << endl;
        cin >> id;
        if (id == "menu") //中止输入的情况
        {
            system("cls");
            Menu();
            break;
        }
        for (i = 1; i <= CntStudent; i++)
        {
            isfind = 0; //初始化变量，未找到该生
            if (student[i].id == id)
            {
                //cout<<"找到此生在"<<i<<"位置！\n";
                cout << "请输入你需要修改的数据(输入数字)：\n";
                cout << "1.学号" << endl;
                cout << "2.性别" << endl;
                cout << "3.姓名" << endl;
                cin >> modify;
                if (modify == 1)
                {
                    string occasional_id;
                    cout << "请输入修改后的学号：\n";
                    cin >> occasional_id;
                    student[i].id = occasional_id;
                }
                else if (modify == 2)
                {
                    int occasional_sex;
                    cout << "请输入修改后的性别：\n";
                    cin >> occasional_sex;
                    student[i].sex = occasional_sex;
                }
                else if (modify == 3)
                {
                    string occasional_name;
                    cout << "请输入修改后的姓名：\n";
                    cin >> occasional_name;
                    student[i].name = occasional_name;
                }
                cout << "修改成功！是否要继续修改学生数据（y/n):";
                char y_or_n;
                cin >> y_or_n;
                if (y_or_n == 'n')
                {
                    system("cls");
                    Menu();
                    isfind = 1;
                    break;
                }
                else
                {
                    isfind = 2;
                    cout << "请输入学号：" << endl;
                    break;
                }
            }
        }
        if (isfind == 1) //此条件用于在找到学生情况下避免下一行的未找到语句出现
            break;
        if (isfind == 0)
            cout << "未找到该生！\n";
    }
}

//搜索学生信息
void SearchRecord(struct form *student)
{
    system("cls");
    string id;
    int isfind = 0, i, j; //是否找到
    while (1)
    {
        isfind = 0;
        cout << "请输入该生学号，输入menu返回菜单：" << endl;
        cin >> id;
        if (id == "menu") //中止输入的情况
        {
            system("cls");
            Menu();
            break;
        }
        for (i = 1; i <= CntStudent; i++)
        {
            if (student[i].id == id)
            {
                cout << "===============\n";
                cout << "姓名：" << student[i].name << endl;
                cout << "学号：" << student[i].id << endl;
                if (student[i].sex == 1)
                    cout << "性别：男" << endl;
                else
                    cout << "性别：女" << endl;
                cout << "总分：" << student[i].sumscore << endl;
                cout << "该生的5门成绩分别为：" << endl;
                for (j = 1; j <= 5; j++)
                {
                    cout << student[i].score[j] << " ";
                }
                cout << "\n\n查询成功！是否要继续查询学生数据（y/n):";
                char y_or_n;
                cin >> y_or_n;
                if (y_or_n == 'n')
                {
                    system("cls");
                    Menu();
                    isfind = 1;
                    break;
                }
                else
                {
                    isfind = 2; //此情况为了避免出现未找到该生语句
                    cout << "请输入学号：" << endl;
                    break;
                }
            }
        }
        if (isfind == 1) //此条件用于在找到学生情况下避免下一行的未找到语句出现
            break;
        if (isfind == 0)
            cout << "未找到该生！\n";
    }
}

//排序函数
void MySort(struct form *student) //调出排序函数界面
{
    system("cls");
    cout << "开始排序......\n";
    cout << "排序成功！输入menu返回主菜单\n";
    string cmd;
    while (1)
    {
        cin >> cmd;
        if (cmd == "menu")
        {
            system("cls");
            Menu();
            break;
        }
    }
}

//总分降序排序函数
bool Descending_sum(struct form a, struct form b)
{
    if (a.sumscore < b.sumscore)
        return a.sumscore > b.sumscore;
    else
        return a.sumscore > b.sumscore;
}

//总分升序排序函数
bool Ascending_sum(struct form a, struct form b)
{
    if (a.sumscore > b.sumscore)
        return a.sumscore < b.sumscore;
    else
        return a.sumscore < b.sumscore;
}

//学号降序排序函数
bool Descending_num(struct form a, struct form b)
{
    if (a.id < b.id)
        return a.id > b.id;
    else
        return a.id > b.id;
}

//学号升序排序函数
bool Ascending_num(struct form a, struct form b)
{
    if (a.id > b.id)
        return a.id < b.id;
    else
        return a.id < b.id;
}

//写文件
void WriteFile(struct form *student)
{
    //创建文件指针方便调用
    FILE *file = fopen("D:/1.txt", "w");
    //打开失败的情况
    if (file == NULL)
    {
        printf("open error!\n");
        exit(1);
    }
    //转字符以便输出
    for (int i = 1; i <= CntStudent; i++)
    {
        //名字
        int k = 0;
        char name[1000];
        while (student[i].name[k] != '\0')
        {
            name[k] = student[i].name[k];
            k++;
        }
        name[k + 1] = '\0';
        fputs(name, file);
        fprintf(file, "\n");
        //学号
        k = 0;
        char id[1000];
        while (student[i].id[k] != '\0')
        {
            id[k] = student[i].id[k];
            k++;
        }
        id[k + 1] = '\0';
        fputs(id, file);
        fprintf(file, "\n\n");
        //总成绩
        int sum_score = student[i].sumscore;
        fprintf(file, "%d", sum_score);
        fprintf(file, "\n");
        //各科成绩
        for (int j; j <= 5; j++)
        {
            int score = student[i].score[j];
            fprintf(file, "%d\n", score);
        }
    }
    fclose(file);
}
