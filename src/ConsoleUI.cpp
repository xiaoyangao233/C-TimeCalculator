#include "ConsoleUI.h"
#include <iostream>
#include <cstdlib>

ConsoleUI::ConsoleUI() : m_PlannedTime(0, 0, 0)
{
	
}

std::string ConsoleUI::collName(int id) const
{
	auto it = m_collections.find(id);
	return it != m_collections.end() ? it->second : "未知合集";
}

std::string ConsoleUI::partName(int id) const
{
	auto it = m_parts.find(id);
	return it != m_parts.end() ? it->second : "未知部分";
}

void ConsoleUI::run()
{
	while (true)
	{
		showMenu();

		switch (readChoice())
		{
		case 2: addRecord(); break;
		case 3: showAll();   break;
		case 0: return;
		default:
			std::cout << "还没有接上这个功能\n";
			break;
		}
	}
}

void ConsoleUI::showMenu() const
{
	std::cout << "*******************************************" << std::endl;
	std::cout << "*******   1、添加应学的视频总时长   *******" << std::endl;
	std::cout << "*******    2、添加已学的视频信息    *******" << std::endl;
	std::cout << "*******   3、显示所有已学视频信息   *******" << std::endl;
	std::cout << "*******    4、删除已学的视频信息    *******" << std::endl;
	std::cout << "*******    5、查找已学的视频信息    *******" << std::endl;
	std::cout << "*******    6、修改已学的视频信息    *******" << std::endl;
	std::cout << "*******        7、显示百分比        *******" << std::endl;
	std::cout << "*******     8、清空所有视频信息     *******" << std::endl;
	std::cout << "*******        0、退出本系统        *******" << std::endl;
	std::cout << "*******************************************" << std::endl;
}
int  ConsoleUI::readChoice() const
{
	int choice = -1;

	if (!(std::cin >> choice))          // 用户输了字母
	{
		std::cin.clear();               // 清掉错误状态
		std::cin.ignore(1000, '\n');    // 丢掉这一行剩下的字符
		return -1;                      // 当成非法选择，让 run() 重新显示菜单
	}

	std::cin.ignore(1000, '\n');        // 丢掉行尾换行，防止污染下一次输入
	return choice;
}

void ConsoleUI::addRecord()
{
	std::string name,line;
	int collectionId = 0, partId = 0, serialId = 0;
	int year = 0, month = 0, day = 0;
	int hour = 0, minute = 0, second = 0;

	std::cout << "请输入视频相关信息：" << std::endl;
	std::cout << "请输入视频名称：" << std::endl;
	std::getline(std::cin >> std::ws, name);
	
	std::cout << "请输入所属集合编号：" << std::endl;
	for (const auto& [id, collname] : m_collections)
	{
		std::cout << id << " --- " << collname << std::endl;
	}
	while (true)
	{
		std::cin >> collectionId;
		if (m_collections.count(collectionId) > 0)   // count 返回 0 或 1
			break;
		std::cout << "没有这个合集编号，请重新输入：";
	}

	std::cout << "请输入部分编号：" << std::endl;
	for (const auto& [id, partname] : m_parts)
	{
		std::cout << id << " --- " << partname << std::endl;
	}
	while (true)
	{
		std::cin >> partId;
		if (m_parts.count(partId) > 0)   // count 返回 0 或 1
			break;
		std::cout << "没有这个合集编号，请重新输入：";
	}

	std::cout << "请输入本视频序号：" << std::endl;
	std::cin >> serialId;


	std::cout << "请输入视频时长：" << std::endl;
	std::cin >> hour >> minute >> second;

	std::cout << "请输入学习日期：" << std::endl;
	std::cin >> year >> month >> day;

	try
	{
		VideoRecord r(name, collectionId, partId, serialId, Time(hour, minute, second), Date(year, month, day));

		if (m_Store.add(r))
		{
			std::cout << "视频添加成功！" << "\n";
		}
		else
		{
			std::cout << "这条记录已存在\n";
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "输入不合法：" << e.what() << "\n";
	}

	//任意键清屏
	system("pause");
	system("cls");
}

void ConsoleUI::showAll() const
{
	std::cout << "合集 | 部分 | 序号 | 名字 | 时长 | 日期\n";

	const auto& records = m_Store.all();
	for (const auto& record : records)
	{
		std::cout << collName(record.getCollectionId()) << " | "
			<< partName(record.getPartId()) << " | "
			<< record.getSerialId() << " | "
			<< record.getName() << " | "
			<< record.getTime().toString() << " | "
			<< record.getDate().toString() << "\n";
	}

	std::cout << "共有" << records.size() << "条数据。\n";

	system("pause");
	system("cls");
}