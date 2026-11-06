#include"Date.h"
#include<stdexcept>
#include<format>

namespace
{
	bool isLeapYear(int year)
	{
		return ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0);
	}

	int dayInMonth(int year, int month)
	{
		static constexpr int DAYS[12] =
		{ 31,28,31,30,31,30,
		 31,31,30,31,30,31
		};

		if (month == 2 && isLeapYear(year))
		{
			return 29;
		}
		return DAYS[month - 1];
	}
}

//含参构造函数
Date::Date(int year, int month, int day)
{
	if (year < 1900)
	{
		throw std::invalid_argument("年不得早于1900！");
	}
	if (month < 1 || month > 12)
	{
		throw std::invalid_argument("月份不得为负或大于十二！");
	}
	if (day < 1 || day > dayInMonth(year,month))
	{
		throw std::invalid_argument("日期不得为负或大于该月日期！");
	}

	this->m_Year = year;
	this->m_Month = month;
	this->m_Day = day;

}

//返回日期字符串
std::string Date::toString() const
{
	return std::format("{:04}-{:02}-{:02}", m_Year, m_Month, m_Day);
}

//统一单位到日
int Date::toDay() const
{
	//基准日为1900-01-01
	int tempDay=0; //存放日期差值

	//计算年数差
	for (int i = 1900; i < m_Year;i++)
	{
		if (isLeapYear(i))
		{
			tempDay += 366;
		}
		else
		{
			tempDay += 365;
		}
	}

	//计算月份差
	for (int i = 1; i < m_Month;i++)
	{
		tempDay += dayInMonth(m_Year, i);
	}

	//计算日期差
	tempDay += m_Day - 1;

	return tempDay;

}