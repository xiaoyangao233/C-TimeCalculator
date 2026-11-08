#pragma once
#include "VideoStore.h"
#include <map>

class ConsoleUI
{
public:
	ConsoleUI();
	void run();

private:
    std::string collName(int id) const;
    std::string partName(int id) const;
	void showMenu() const;
	int  readChoice() const;

	void addRecord();
	void showAll() const;
    void removeRecord();
    void findRecord();
    void modifyRecord();
    void clearRecord();

	VideoStore m_Store;
	Time m_PlannedTime;

    int readInt() const;   // 保证返回一个数字
    int readCollectionId() const;                   // 保证是菜单里有的合集
    int readPartId() const;                         // 保证是菜单里有的部分

    //临时存放一下第一个合集
    std::map<int, std::string> m_parts =
    {
        {1, "第一部分 C++入门"},
        {2, "第二部分 C++核心编程"},
        {3, "第三部分 C++提高课程"},
        {4, "通讯录管理系统"},
        {5, "职工管理系统"},
        {6, "演讲比赛流程管理系统"},
        {7, "机房预约系统"},
    };

    std::map<int, std::string> m_collections = { {1,"黑马程序员C++"} };
};