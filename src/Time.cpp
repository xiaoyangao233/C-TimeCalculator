#include "Time.h"
#include<stdexcept>

//含参构造函数，初始化
Time::Time(int hour, int minute, int second) : m_Hour(0), m_Minute(0), m_Second(0)
{
	//判断输入是否合法
	if (hour < 0 || minute < 0 || second < 0)
	{
		throw std::invalid_argument("Time：时间输入不能为负");
	}
	
	//从秒开始进行归一化
	if (second >= 60)
	{
		this->m_Second = second % 60;
		minute += second / 60;
	}
	else
	{
		this->m_Second = second;
	}

	if (minute >= 60)
	{
		this->m_Minute = minute % 60;
		hour += minute / 60;
	}
	else
	{
		this->m_Minute = minute;
	}

	this->m_Hour = hour;

}

//显示时长信息函数
std::string Time::toString() const
{
	std::string s;

	//依次判断时分秒位数并加入到字符串后
	if (this->m_Hour < 10)
	{
		s += '0';
	}
	s += std::to_string(m_Hour);
	s += ':';

	if (this->m_Minute < 10)
	{
		s += '0';
	}
	s += std::to_string(m_Minute);
	s += ':';

	if (this->m_Second < 10)
	{
		s += '0';
	}
	s += std::to_string(m_Second);

	return s;
}

//单位化为秒函数	
long long Time::toSeconds() const
{

	return this->m_Hour * 3600LL + this->m_Minute * 60LL + this->m_Second;

}

//时长加法运算符重载
Time Time::operator+(const Time& rhs) const
{
	int hour, minute, second;
	hour = this->m_Hour + rhs.m_Hour;
	minute = this->m_Minute + rhs.m_Minute;
	second = this->m_Second + rhs.m_Second;

	return Time(hour, minute, second);
	
}
