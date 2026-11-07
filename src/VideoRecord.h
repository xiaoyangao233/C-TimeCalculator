#pragma once
#include <string>
#include "Time.h"
#include "Date.h"

class VideoRecord
{
public:
	
	//构造函数
	VideoRecord(const std::string& name, int collectionId, int partId, int serialId, Time time, Date date);

	//打印函数
	std::string toString() const;

	//返回时长和日期
	Time getTime() const;
	Date getDate() const;

	//判断该对象是否位于某部分
	bool isIn(int collectionId, int partId) const;

	//判断编号组合是否是该对象有的
	bool isAt(int collectionId, int partId, int serialId) const;

	//获取属性
	std::string getName() const;
	int getCollectionId() const;
	int getPartId() const;
	int getSerialId() const;

private:
	std::string m_Name; //存视频的名字
	int m_CollectionId; //存所属合集的编号
	int m_PartId; //存合集下部分/章节的编号
	int m_SerialId; //存部分下的编号
	Time m_Time; //存该视频的时长
	Date m_Date; //存该视频的学习日期

};