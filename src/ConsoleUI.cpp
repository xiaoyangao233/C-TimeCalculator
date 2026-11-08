#include "ConsoleUI.h"
#include <iostream>
#include <cstdlib>

namespace
{
	const std::string DATA_FILE = "videos.txt";
}

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

int ConsoleUI::readInt() const
{
	int value = 0;
	while (true)
	{
		if (std::cin >> value)
		{
			std::cin.ignore(1000, '\n');   // ← 成功时也把这一行清干净
			return value;
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "请输入数字：\n";
	}
}

int ConsoleUI::readCollectionId() const
{
	while (true)
	{
		int id = readInt();
		if (m_collections.count(id) > 0)
			return id;
		std::cout << "没有这个合集编号，请重新输入：\n";
	}
}

int ConsoleUI::readPartId() const
{
	while (true)
	{
		int id = readInt();
		if (m_parts.count(id) > 0)
			return id;
		std::cout << "没有这个部分编号，请重新输入：\n";
	}
}


void ConsoleUI::run()
{
	if (!m_Store.loadFrom(DATA_FILE))
		std::cout << "（没有找到存档，按空库启动）\n";

	while (true)
	{
		showMenu();

		switch (readChoice())
		{
		case 2: addRecord(); break;
		case 3: showAll();   break;
		case 4: removeRecord(); break;
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
	std::string name;

	std::cout << "请输入视频相关信息：" << std::endl;
	std::cout << "请输入视频名称：" << std::endl;
	std::getline(std::cin >> std::ws, name);
	
	std::cout << "请输入所属集合编号：" << std::endl;
	for (const auto& [id, collname] : m_collections)
		std::cout << id << " --- " << collname << std::endl;
	int collectionId = readCollectionId();

	std::cout << "请输入部分编号：" << std::endl;
	for (const auto& [id, partname] : m_parts)
		std::cout << id << " --- " << partname << std::endl;
	int partId = readPartId();

	std::cout << "请输入视频序号： " << std::endl;
	int serialId = readInt();

	std::cout << "请输入视频时长\n";
	std::cout << "  时：";  int hour = readInt();
	std::cout << "  分：";  int minute = readInt();
	std::cout << "  秒：";  int second = readInt();

	std::cout << "请输入学习日期\n";
	std::cout << "  年：";  int year = readInt();
	std::cout << "  月：";  int month = readInt();
	std::cout << "  日：";  int day = readInt();

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

	m_Store.saveTo(DATA_FILE);

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

void ConsoleUI::removeRecord()
{
	std::cout << "请输入所属集合编号：" << std::endl;
	for (const auto& [id, collname] : m_collections)
		std::cout << id << " --- " << collname << std::endl;
	int collectionId = readCollectionId();

	std::cout << "请输入部分编号：" << std::endl;
	for (const auto& [id, partname] : m_parts)
		std::cout << id << " --- " << partname << std::endl;
	int partId = readPartId();

	std::cout << "请输入视频序号： " << std::endl;
	int serialId = readInt();

	if (!m_Store.remove(collectionId, partId, serialId))
	{
		std::cout << "这条记录不存在！" << std::endl;
	}
	else
	{
		std::cout << "已成功删除本视频！" << std::endl;
	}

	m_Store.saveTo(DATA_FILE);

	system("pause");
	system("cls");
}