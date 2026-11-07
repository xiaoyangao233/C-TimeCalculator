#include<format>
#include<stdexcept>
#include"VideoRecord.h"

//构造函数
VideoRecord::VideoRecord(const std::string& name, int collectionId, int partId, int serialId, Time time, Date date) : m_Name(name), m_CollectionId(collectionId), m_PartId(partId), m_SerialId(serialId), m_Time(time), m_Date(date)
{
	if (name == "")
	{
		throw std::invalid_argument("VideoRecord：名字不能为空！");
	}
	
	if (collectionId < 1 || partId < 1 || serialId < 1)
	{
		throw std::invalid_argument("VideoRecord：编号必须从 1 开始！");
	}
}

//打印函数
std::string VideoRecord::toString() const
{
	return std::format("{} | {} | {} | {}", m_SerialId, m_Name, m_Time.toString(), m_Date.toString());
}

//返回时长
Time VideoRecord::getTime() const
{
	return m_Time;
}

Date VideoRecord::getDate() const
{
	return m_Date;
}

//判断该对象是否位于某部分
bool VideoRecord::isIn(int collectionId, int partId) const
{
	return m_CollectionId == collectionId && m_PartId == partId;
}

//判断编号组合是否是该对象有的
bool VideoRecord::isAt(int collectionId, int partId, int serialId) const
{
	return (m_CollectionId == collectionId && m_PartId == partId && m_SerialId == serialId);
}

//获取属性
std::string VideoRecord::getName() const
{
	return this->m_Name;
}

int VideoRecord::getCollectionId() const
{
	return this->m_CollectionId;
}

int VideoRecord::getPartId() const
{
	return this->m_PartId;
}

int VideoRecord::getSerialId() const
{
	return this->m_SerialId;
}
