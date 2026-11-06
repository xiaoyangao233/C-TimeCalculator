#include "SelfTest.h"
#include<iostream>
#include "VideoRecord.h"
#include<stdexcept>
#include"VideoStore.h"

namespace
{
	//检查小助手
	void check(bool ok, const std::string& what)
	{
		std::cout << (ok ? "[通过] " : "[失败] ") << what << "\n";
	}

	//接收日期异常小助手
	bool okDate(int year, int month, int day)
	{
		try 
		{ 
			Date probe(year, month, day);
			return true;
		}
		catch (const std::invalid_argument&) 
		{ 
			return false; 
		}
	}

	bool okTime(int hour, int minute, int second)
	{
		try
		{
			Time probe(hour, minute, second);
			return true;
		}
		catch (const std::invalid_argument&)
		{
			return false;
		}
	}
}

//测试代码存放处
void runSelfTest() 
{

	// Date 的几个关键边界（不用那张大表，抓重点就够）
	check(okDate(2024, 2, 29), "2024 闰年 2 月 29");
	check(okDate(1900, 2, 28), "1900 不是闰年，2 月只有 28 天");
	check(!okDate(1900, 2, 29), "1900 年没有 2 月 29");
	check(!okDate(2024, 4, 31), "4 月没有 31 号");
	check(Date(2000, 1, 1).toDay() == 36524, "世纪锚点");
	check(Date(2026, 11, 6).toDay() - Date(2026, 11, 5).toDay() == 1, "相邻两天差 1");

	// Time
	check(Time(1, 90, 30).toString() == "02:30:30", "Time 归一化");
	check(Time(0, 0, 3661).toString() == "01:01:01", "Time 进位");
	check(Time(2, 30, 30).toSeconds() + Time(0, 45, 45).toSeconds() == Time(3, 16, 15).toSeconds(), "秒数相加");
	check(!okTime(-1, 0, 0), "Time 负值应该抛异常");
	check(okTime(0, 90, 0), "Time 90 分钟能正常归一化");

	// VideoRecord 测试
	VideoRecord r("循环嵌套", 1, 2, 5, Time(0, 25, 30), Date(2026, 11, 6));

	check(r.toString() == "5 | 循环嵌套 | 00:25:30 | 2026-11-06", "toString 格式");
	check(r.getTime().toSeconds() == 1530, "getTime");
	check(r.isIn(1, 2) == true, "isIn 命中");
	check(r.isIn(1, 3) == false, "isIn 不命中");
	check(r.isAt(1, 2, 5) == true, "isAt 命中");
	check(r.isAt(1, 2, 6) == false, "isAt 不命中");

	bool threw = false;
	try { VideoRecord bad("", 1, 2, 5, Time(0, 0, 30), Date(2026, 11, 6)); }
	catch (const std::invalid_argument&) { threw = true; }
	check(threw, "空名字应该抛异常");

	threw = false;
	try { VideoRecord bad("你好", 0, 2, 5, Time(0, 0, 30), Date(2026, 11, 6)); }
	catch (const std::invalid_argument&) { threw = true; }
	check(threw, "合集号0应该抛异常");

	threw = false;
	try { VideoRecord bad("你好", 1, 0, 5, Time(0, 0, 30), Date(2026, 11, 6)); }
	catch (const std::invalid_argument&) { threw = true; }
	check(threw, "部分号0应该抛异常");

	threw = false;
	try { VideoRecord bad("你好", 1, 2, 0, Time(0, 0, 30), Date(2026, 11, 6)); }
	catch (const std::invalid_argument&) { threw = true; }
	check(threw, "序号0应该抛异常");

	// ---VideoStore测试---

	// ===== 增删改 =====
	{
		VideoStore s;
		VideoRecord r1("循环嵌套", 1, 2, 5, Time(0, 25, 30), Date(2026, 11, 6));
		check(s.add(r1), "首次添加成功");
		check(!s.add(r1), "重复添加失败");
		check(s.all().size() == 1, "重复添加没真的加进去");

		check(s.modify(1, 2, 5, VideoRecord("改名", 1, 2, 5, Time(0, 30, 0), Date(2026, 11, 6))),
			"改自己编号能成功");
		check(s.all().size() == 1, "modify 没增加条数");

		check(s.find(1, 2, 5) != nullptr, "find 找得到");
		check(s.find(1, 2, 9) == nullptr, "find 找不到返回 nullptr");

		s.add(VideoRecord("指针", 1, 2, 6, Time(1, 10, 0), Date(2026, 11, 7)));
		check(!s.modify(1, 2, 5, VideoRecord("撞号", 1, 2, 6, Time(0, 1, 0), Date(2026, 11, 6))),
			"撞别人的编号要失败");
		check(s.all().size() == 2, "撞号失败后条数没变");
		check(!s.remove(1, 2, 99), "删不存在的返回 false");
	}

	// ===== 统计（全新容器，没被前面的操作碰过）=====
	{
		VideoStore s;
		s.add(VideoRecord("循环嵌套", 1, 2, 5, Time(0, 25, 30), Date(2026, 11, 6)));
		s.add(VideoRecord("指针", 1, 2, 6, Time(1, 10, 0), Date(2026, 11, 7)));
		s.add(VideoRecord("别的课", 2, 1, 1, Time(0, 10, 0), Date(2026, 11, 8)));

		check(s.totalTimeOfPart(1, 2).toSeconds() == 5730, "部分总时长 1:35:30");
		check(s.totalTimeOfCollection(1).toSeconds() == 5730, "合集 1 总时长");
		check(s.totalTimeOfCollection(2).toSeconds() == 600, "合集 2 总时长");
		check(s.totalTimeOfPart(1, 9).toSeconds() == 0, "空部分返回 0");
	}
}
