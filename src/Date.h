#pragma once
#include<string>

class Date
{
private:
	int m_Year;
	int m_Month;
	int m_Day;

public:

	//含参构造函数
	Date(int year, int month, int day);

	//返回日期字符串
	std::string toString() const;

	//统一单位到日
	int toDay() const;

};