#pragma once
#include<string>

class Time
{
public:

	//含参构造函数，初始化
	Time(int hour, int minute, int second);

	//显示时长信息函数
	std::string toString() const;

	//单位化为秒函数	
	long long toSeconds() const;

	//时长加法运算符重载
	Time operator+(const Time& rhs) const;

private:
	int m_Hour; //时
	int m_Minute; //分
	int m_Second; //秒
};