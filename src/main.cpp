#include<iostream>
#include<string>
#include<iomanip>
#include <windows.h>
#include"SelfTest.h"
using namespace std;
#define MAX 1000

//创建视频信息结构体
struct Video {

	//部分
	int m_Part;
	//在部分中的序号
	int m_Number;
	//视频时长（包含时分秒）
	int m_Time[3];
	//学习日期
	string m_Date;

};

//创建视频信息合集结构体
struct VideoTotal
{
	
	//该合集中保存的视频信息数组
	struct Video videoArray[MAX];

	//合集中保存的视频信息个数
	int m_Size;
};

//创建结构体存放总时长
struct VideoTimeSum
{

	//一个数组存放时分秒
	int m_TimeSum[3] = { 0,0,0 };

};

//已学视频总时长计算
void timeTotal(VideoTotal* vt, int timeArray[])
{
	int hours = 0, min = 0, sec = 0;//初始化时分秒变量

	//开始计算
	for (int i = 0;i < vt->m_Size;i++)
	{
		hours += vt->videoArray[i].m_Time[0];
		min += vt->videoArray[i].m_Time[1];
		sec += vt->videoArray[i].m_Time[2];
	}

	//化简
	min += (sec / 60);
	sec %= 60; //将秒化为分钟

	hours += (min / 60);
	min %= 60; //将分钟化为小时


	//将信息存入数组
	*(timeArray) = hours;
	*(timeArray+1) = min;
	*(timeArray+2) = sec;

}

//1、添加视频总时长
void addVideoSum(VideoTimeSum* vts) {
	
	cout << "请输入你正在学习的视频总时长：" << endl;
	cout << "（按时分秒顺序输入，每个数据用空格隔开）" << endl;
	int VideoSumArray[3];//用来存放时分秒

	//遍历存入数组中，并检测输入是否合法
	while (true)
	{

		for (int i = 0; i < 3; i++)
		{
			cin >> VideoSumArray[i];
		}

		//检测是否合法
		if (VideoSumArray[1] >= 60 || VideoSumArray[1] < 0 ||
			VideoSumArray[2] >= 60 || VideoSumArray[2] < 0)
		{
			cout << "数据输入有误，请重新输入:" << endl;
		}
		else
		{
			vts->m_TimeSum[0] = VideoSumArray[0];
			vts->m_TimeSum[1] = VideoSumArray[1];
			vts->m_TimeSum[2] = VideoSumArray[2];
			break;
		}
	}


	cout << "信息记录完成！" << endl;
	cout << "总视频时长为：";
	for (int i = 0; i < 3;i++)
	{
		if (vts->m_TimeSum[i] < 10 && vts->m_TimeSum[i] >= 0)
		{
			cout << "0" << vts->m_TimeSum[i];
		}
		else
		{
			cout << vts->m_TimeSum[i];
		}
		if (i != 2)
			cout << ":";
	}
	cout << endl;

	//任意键清屏
	system("pause");
	system("cls");
	
}


//2、添加已学视频信息
void addVideo(VideoTotal* vt)
{
	if (vt->m_Size == MAX)
	{
		cout << "视频记录已满，无法添加！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		//添加具体视频信息

		//属于第几部分
		int part;
		cout << "请输入属于第几部分：" << endl;
		cout << "1 --- 第一部分 C++入门" << endl;
		cout << "2 --- 第二部分 C++核心编程" << endl;
		cout << "3 --- 第三部分 C++提高课程" << endl;
		cout << "4 --- 通讯录管理系统" << endl;
		cout << "5 --- 职工管理系统" << endl;
		cout << "6 --- 演讲比赛流程管理系统" << endl;
		cout << "7 --- 机房预约系统" << endl;
		while (true) {

			cin >> part;

			//输入正确1~7可退出循环
			//否则重来

			if (part > 0 && part < 8)
			{
				vt->videoArray[vt->m_Size].m_Part = part;
				break;
			}
			else
			{
				cout << "输入有误，请重新输入：" << endl;
			}
		}
		

		//序号
		int number;
		cout << "请输入视频序号： " << endl;
		cin >> number;
		vt->videoArray[vt->m_Size].m_Number = number;

		//视频时长
		int time;
		cout << "请输入时长：" << endl;
		cout << "（按时分秒顺序输入，每个数据用空格隔开）" << endl;

		//输入时长并判断是否合法
		while (true)
		{

			for (int i = 0; i < 3;i++)
			{
				cin >> time;
				vt->videoArray[vt->m_Size].m_Time[i] = time;
			}

			//判断
			if (vt->videoArray[vt->m_Size].m_Time[1] >= 60 || vt->videoArray[vt->m_Size].m_Time[1] < 0 ||
				vt->videoArray[vt->m_Size].m_Time[2] >= 60 || vt->videoArray[vt->m_Size].m_Time[2] < 0)
			{
				cout << "数据输入有误，请重新输入： " << endl;
			}
			else 
			{
				break;
			}
		}

		//日期
		string date;
		cout << "请输入学习日期： " << endl;
		cout << "格式为：年.月.日  例如：26.9.27" << endl;
		cin >> date;
		vt->videoArray[vt->m_Size].m_Date = date;

		//更新合集数量
		vt->m_Size++;

		cout << "添加成功！" << endl;
		cout << "当前视频数为： " << vt->m_Size << endl;

		//任意键清屏
		system("pause");
		system("cls");

	}
}


//3、显示所有视频信息
void showVideo(VideoTotal* vt) 
{

	//判断合集是否为0，如果为0，提示记录为空
	//如果不为0，则显示合集里的视频信息

	if (vt->m_Size == 0) {
		cout << "当前的记录为空" << endl;
	}
	else
	{
		cout <<left<< setw(25) << "部分" << setw(6) << "序号" << setw(10) << "时长" << setw(10) << "日期" << endl;
		for (int i = 0; i < vt->m_Size;i++) {
			//输出所属部分
			cout <<left<< setw(25);
			switch (vt->videoArray[i].m_Part)
			{
			case 1:
				cout << "第一部分 C++入门";
				break;
			case 2:
				cout << "第二部分 C++核心编程";
				break;
			case 3:
				cout << "第三部分 C++提高课程";
				break;
			case 4:
				cout << "通讯录管理系统";
				break;
			case 5:
				cout << "职工管理系统";
				break;
			case 6:
				cout << "演讲比赛流程管理系统";
				break;
			case 7:
				cout << "机房预约系统";
				break;
			}
			cout << setw(6) << vt->videoArray[i].m_Number; //输出序号

			//输出时长
			for (int j = 0; j < 3; j++)
			{
				if (vt->videoArray[i].m_Time[j] < 10 && vt->videoArray[i].m_Time[j] >= 0)
				{
					cout << "0" << vt->videoArray[i].m_Time[j];
				}
				else
				{
					cout << vt->videoArray[i].m_Time[j];
				}
				if (j != 2)
					cout << ":";
			}
			cout << "  ";

			//输出日期
			cout << setw(10) << vt->videoArray[i].m_Date << endl;

		}
		cout << "总视频数为： " << vt->m_Size << "个" << endl;
	}

	//任意键清屏
	system("pause");
	system("cls");

}


//查找视频是否存在
int isExist(VideoTotal* vt, int part, int number)
{
	for (int i = 0; i <= vt->m_Size ; i++)
	{
		//查找是否一样
		if (vt->videoArray[i].m_Part == part && vt->videoArray[i].m_Number == number) {
			return i;//找到了，返回具体位置
		}
	}
	return -1;//没找到，返回-1
}


//4、删除视频信息
void deleteVideo(VideoTotal* vt)
{

	cout << "请输入您要删除的视频信息的部分编号及序号（数据之间用空格隔开）" << endl;
	cout << "部分编号表↓" << endl;
	cout << "1 --- 第一部分 C++入门" << endl;
	cout << "2 --- 第二部分 C++核心编程" << endl;
	cout << "3 --- 第三部分 C++提高课程" << endl;
	cout << "4 --- 通讯录管理系统" << endl;
	cout << "5 --- 职工管理系统" << endl;
	cout << "6 --- 演讲比赛流程管理系统" << endl;
	cout << "7 --- 机房预约系统" << endl;

	int number, part;

	while (true) //检测输入是否正确
	{
		cin >> part >> number;

		if (part >= 1 && part <= 7)
		{
			break;
		}

		cout << "输入有误，请重新输入：" << endl;

	}


	//ret == -1 没有查到    ret != -1 查到了
	int ret = isExist(vt, part, number);

	if (ret != -1)
	{
		//查找到信息，进行删除操作

		for (int i = ret;i < vt->m_Size;i++)
		{
			//数据前移
			vt->videoArray[i] = vt->videoArray[i + 1];
		}
		vt->m_Size--; //更新视频个数
		cout << "删除成功" << endl;

	}
	else
	{
		cout << "暂未查到该视频信息" << endl;
	}

	system("pause");
	system("cls");

}


//5、查找视频信息
void findVideo(VideoTotal * vt)
{
	
	cout << "请输入您要查找的视频信息的部分编号及序号（数据之间用空格隔开）" << endl;
	cout << "部分编号表↓" << endl;
	cout << "1 --- 第一部分 C++入门" << endl;
	cout << "2 --- 第二部分 C++核心编程" << endl;
	cout << "3 --- 第三部分 C++提高课程" << endl;
	cout << "4 --- 通讯录管理系统" << endl;
	cout << "5 --- 职工管理系统" << endl;
	cout << "6 --- 演讲比赛流程管理系统" << endl;
	cout << "7 --- 机房预约系统" << endl;

	int number, part;

	while (true) //检测输入是否正确
	{
		cin >> part >> number;

		if (part >= 1 && part <= 7)
		{
			break;
		}

		cout << "输入有误，请重新输入：" << endl;

	}

	int ret = isExist(vt, part, number);

	if (ret != -1)
	{
		
		cout << left << setw(25) << "部分" << setw(6) << "序号" << setw(10) << "时长" << setw(10) << "日期" << endl;
		cout << left << setw(25);
		switch (vt->videoArray[ret].m_Part)
		{
		case 1:
			cout << "第一部分 C++入门";
			break;
		case 2:
			cout << "第二部分 C++核心编程";
			break;
		case 3:
			cout << "第三部分 C++提高课程";
			break;
		case 4:
			cout << "通讯录管理系统";
			break;
		case 5:
			cout << "职工管理系统";
			break;
		case 6:
			cout << "演讲比赛流程管理系统";
			break;
		case 7:
			cout << "机房预约系统";
			break;
		}
		cout << setw(6) << vt->videoArray[ret].m_Number; //输出序号

		//输出时长
		for (int j = 0; j < 3; j++)
		{
			if (vt->videoArray[ret].m_Time[j] < 10 && vt->videoArray[ret].m_Time[j] >= 0)
			{
				cout << "0" << vt->videoArray[ret].m_Time[j];
			}
			else
			{
				cout << vt->videoArray[ret].m_Time[j];
			}
			if (j != 2)
				cout << ":";
		}
		cout << "  ";

		//输出日期
		cout << setw(10) << vt->videoArray[ret].m_Date << endl;

	}
	else
	{
		cout << "暂未查到该视频信息" << endl;
	}

	system("pause");
	system("cls");

}


//6、修改视频信息
void modifyVideo(VideoTotal* vt)
{

	cout << "请输入您要查找的视频信息的部分编号及序号（数据之间用空格隔开）" << endl;
	cout << "部分编号表↓" << endl;
	cout << "1 --- 第一部分 C++入门" << endl;
	cout << "2 --- 第二部分 C++核心编程" << endl;
	cout << "3 --- 第三部分 C++提高课程" << endl;
	cout << "4 --- 通讯录管理系统" << endl;
	cout << "5 --- 职工管理系统" << endl;
	cout << "6 --- 演讲比赛流程管理系统" << endl;
	cout << "7 --- 机房预约系统" << endl;

	int number, part;

	while (true) //检测输入是否正确
	{
		cin >> part >> number;

		if (part >= 1 && part <= 7)
		{
			break;
		}

		cout << "输入有误，请重新输入：" << endl;

	}

	int ret = isExist(vt, part, number);

	if (ret != -1)
	{
		//查找到信息，进行修改操作

		//属于第几部分
		system("cls");

		int part;
		cout << "请输入属于第几部分：" << endl;
		cout << "1 --- 第一部分 C++入门" << endl;
		cout << "2 --- 第二部分 C++核心编程" << endl;
		cout << "3 --- 第三部分 C++提高课程" << endl;
		cout << "4 --- 通讯录管理系统" << endl;
		cout << "5 --- 职工管理系统" << endl;
		cout << "6 --- 演讲比赛流程管理系统" << endl;
		cout << "7 --- 机房预约系统" << endl;
		while (true) {

			cin >> part;

			//输入正确1~7可退出循环
			//否则重来

			if (part > 0 && part < 8)
			{
				vt->videoArray[ret].m_Part = part;
				break;
			}
			else
			{
				cout << "输入有误，请重新输入：" << endl;
			}
		}


		//序号
		int number;
		cout << "请输入视频序号： " << endl;
		cin >> number;
		vt->videoArray[ret].m_Number = number;

		//视频时长
		int time;
		cout << "请输入时长：" << endl;
		cout << "（按时分秒顺序输入，每个数据用空格隔开）" << endl;

		//输入时长并判断是否合法
		while (true)
		{

			for (int i = 0; i < 3;i++)
			{
				cin >> time;
				vt->videoArray[ret].m_Time[i] = time;
			}

			//判断
			if (vt->videoArray[ret].m_Time[1] >= 60 || vt->videoArray[ret].m_Time[1] < 0 ||
				vt->videoArray[ret].m_Time[2] >= 60 || vt->videoArray[ret].m_Time[2] < 0)
			{
				cout << "数据输入有误，请重新输入： " << endl;
			}
			else
			{
				break;
			}
		}

		//日期
		string date;
		cout << "请输入学习日期： " << endl;
		cout << "格式为：年.月.日  例如：26.9.27" << endl;
		cin >> date;
		vt->videoArray[ret].m_Date = date;

	}
	else
	{
		cout << "暂未查到该视频信息" << endl;
	}

	system("pause");
	system("cls");

}


//7、显示百分比
void showPercent(VideoTotal* vt, VideoTimeSum* vts)
{
	
	int timeArray[3];
	timeTotal(vt, timeArray);

	//计算总时长
	int ZtimeSum=0, YtimeSum=0, ktime=3600;
	for (int i = 0; i < 3;i++) 
	{
		ZtimeSum += (vts->m_TimeSum[i] * ktime);
		ktime /= 60;
	}

	ktime = 3600;

	for (int i = 0; i < 3;i++)
	{
		YtimeSum += (timeArray[i] * ktime);
		ktime /= 60;
	}


	
	//检测被除数是否为零
	if (ZtimeSum == 0)
	{
		cout << "OMG貌似还没有应学视频的信息呢"<<endl;

		system("pause");
		system("cls");

	}
	else {

		double Percent;
		Percent = (double(YtimeSum) / double(ZtimeSum)) * 100;

		cout << "总共应学视频时长：";
		for (int i = 0; i < 3;i++)
		{
			if (vts->m_TimeSum[i] < 10 && vts->m_TimeSum[i] >= 0)
			{
				cout << "0" << vts->m_TimeSum[i];
			}
			else
			{
				cout << vts->m_TimeSum[i];
			}
			if (i != 2)
				cout << ":";
		}
		cout << endl;

		cout << "当前已学视频时长：";

		for (int i = 0; i < 3;i++)
		{
			if (timeArray[i] < 10 && timeArray[i] >= 0)
			{
				cout << "0" << timeArray[i];
			}
			else
			{
				cout << timeArray[i];
			}
			if (i != 2)
				cout << ":";
		}
		cout << endl;


		if (Percent >= 0 && Percent < 10)
		{
			cout << "□□□□□□□□□□  ";
		}
		else if (Percent >= 10 && Percent < 20)
		{
			cout << "■□□□□□□□□□  ";
		}
		else if (Percent >= 20 && Percent < 30)
		{
			cout << "■■□□□□□□□□  ";
		}
		else if (Percent >= 30 && Percent < 40)
		{
			cout << "■■■□□□□□□□  ";
		}
		else if (Percent >= 40 && Percent < 50)
		{
			cout << "■■■■□□□□□□  ";
		}
		else if (Percent >= 50 && Percent < 60)
		{
			cout << "■■■■■□□□□□  ";
		}
		else if (Percent >= 60 && Percent < 70)
		{
			cout << "■■■■■■□□□□  ";
		}
		else if (Percent >= 70 && Percent < 80)
		{
			cout << "■■■■■■■□□□  ";
		}
		else if (Percent >= 80 && Percent < 90)
		{
			cout << "■■■■■■■■□□  ";
		}
		else if (Percent >= 90 && Percent < 100)
		{
			cout << "■■■■■■■■■□  ";
		}
		else if (Percent == 100)
		{
			cout << "■■■■■■■■■■  ";
		}
		else
		{
			cout << "bro你这不对吧你自己看看： ";
		}

		cout << Percent << "%" << endl;

		system("pause");
		system("cls");

	}

	
}


//8.清空所有信息
void clearVideo(VideoTotal* vt, VideoTimeSum * vts)
{
	cout << "bro 你真的要清除所有信息吗？" << endl;
	int select;
	while (true) {

		cout << "1 --- Yes" << endl;
		cout << "2 --- No" << endl;
		cin >> select;

		if (select == 1) {
			cout << "好吧" << endl;
			vt->m_Size = 0; //做逻辑清空
			cout << "已学视频信息已清除" << endl;
			vts->m_TimeSum[0] = 0;
			vts->m_TimeSum[1] = 0;
			vts->m_TimeSum[2] = 0;
			cout << "应学视频信息已清除" << endl;
			break;
		}
		else if (select == 2)
		{
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "bro输入有误，请重新输入" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}


//菜单界面
void showMenu()
{
	cout << "*******************************************" << endl;
	cout << "*******   1、添加应学的视频总时长   *******" << endl;
	cout << "*******    2、添加已学的视频信息    *******" << endl;
	cout << "*******   3、显示所有已学视频信息   *******" << endl;
	cout << "*******    4、删除已学的视频信息    *******" << endl;
	cout << "*******    5、查找已学的视频信息    *******" << endl;
	cout << "*******    6、修改已学的视频信息    *******" << endl;
	cout << "*******        7、显示百分比        *******" << endl;
	cout << "*******     8、清空所有视频信息     *******" << endl;
	cout << "*******        0、退出本系统        *******" << endl;
	cout << "*******************************************" << endl;
}



int main() {

	SetConsoleOutputCP(CP_UTF8);   // 输出用 UTF-8
	SetConsoleCP(CP_UTF8);         // 输入用 UTF-8（可选）

	runSelfTest();

	//创建合集结构体变量
	VideoTotal vt;
	//初始化合集当前视频个数
	vt.m_Size = 0;

	//创建存放总时长的量
	VideoTimeSum vts;

	int select = 0; //创建用户选择输入的变量

	while (true)
	{

		//菜单调用
		showMenu();

		//用户输入选择的数
		cin >> select;

		switch (select)
		{
		case 1: //添加应学时长
			addVideoSum(&vts);
			break;
		case 2: //添加已学视频信息
			addVideo(&vt);
			break;
		case 3: //显示所有已学视频信息
			showVideo(&vt);
			break;
		case 4: //删除已学视频信息
			deleteVideo(&vt);
			break;
		case 5: //查找已学视频信息
			findVideo(&vt);
			break;
		case 6: //按照部分序号修改已学视频信息
			modifyVideo(&vt);
			break;
		case 7: //显示完成百分比
			showPercent(&vt, &vts);
			break;
		case 8: //清空所有信息
			clearVideo(&vt, &vts);
			break;
		case 0: //退出系统
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}

	}

	system("pause");

	return 0;

}