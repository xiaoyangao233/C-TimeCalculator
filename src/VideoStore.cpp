#include"VideoStore.h"
#include<fstream>
#include<sstream>
#include<stdexcept>

bool VideoStore::add(const VideoRecord& r)
{
	if (indexOf(r.getCollectionId(), r.getPartId(), r.getSerialId()) >= 0)
	{
		return false;
	}

	m_Records.push_back(r);
	return true;

}

bool VideoStore::remove(int collectionId, int partId, int serialId)
{
	int ret = indexOf(collectionId, partId, serialId);
	if (ret < 0)
		return false;
	m_Records.erase(m_Records.begin() + ret);
	return true;
}

bool VideoStore::modify(int collectionId, int partId, int serialId, const VideoRecord& r)
{
	int target = indexOf(collectionId, partId, serialId);
	if (target < 0)
		return false;                                    // 原记录不存在

	int clash = indexOf(r.getCollectionId(), r.getPartId(), r.getSerialId());
	if (clash >= 0 && clash != target)
		return false;                                    // 和"别人"撞号

	m_Records[target] = r;                               // 整条替换
	return true;
}


const VideoRecord* VideoStore::find(int collectionId, int partId, int serialId) const
{
	int ret = indexOf(collectionId, partId, serialId);
	if (ret < 0)
		return nullptr;
	return &m_Records[ret];
}

const std::vector<VideoRecord>& VideoStore::all() const
{
	return m_Records;
}


Time VideoStore::totalTimeOfPart(int collectionId, int partId) const
{
	Time total(0, 0, 0);
	for (const auto& r : m_Records)
	{
		if (r.isIn(collectionId, partId))
		{
			total =total + r.getTime();
		}
	}
	return total;
}

Time VideoStore::totalTimeOfCollection(int collectionId) const
{
	Time total(0, 0, 0);
	for (const auto& r : m_Records)
	{
		if (r.getCollectionId() == collectionId)
		{
			total = total + r.getTime();
		}
	}
	return total;
}

bool VideoStore::saveTo(const std::string& path) const
{
	std::ofstream out(path);
	if (!out)
	{
		return false; // 打不开（目录不存在/没权限）
	}

	for (const auto& r : m_Records)
	{
		out << r.getCollectionId() << ' '
			<< r.getPartId() << ' '
			<< r.getSerialId() << ' '
			<< r.getTime().toString() << ' '
			<< r.getDate().toString() << ' '
			<< r.getName() << '\n';
	}
	return true;
}

bool VideoStore::loadFrom(const std::string& path)
{
	m_Records.clear();

	std::ifstream in(path);
	if (!in)
		return false;  // 文件不存在或打不开

	std::string line;
	while (std::getline(in, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);

		int c, p, s;
		std::string timeStr, dateStr, name;

		iss >> c >> p >> s >> timeStr >> dateStr;
		std::getline(iss >> std::ws, name);  //	剩下的全是名字

		try
		{
			VideoRecord r(name, c, p, s,
				Time(std::stoi(timeStr.substr(0, 2)),
					std::stoi(timeStr.substr(3, 2)),
					std::stoi(timeStr.substr(6, 2))),
				Date(std::stoi(dateStr.substr(0, 4)),
					std::stoi(dateStr.substr(5, 2)),
					std::stoi(dateStr.substr(8, 2))));

			if (!add(r))
			{
				m_Records.clear();
				return false;            // 文件里有重复编号 → 判定为损坏
			}
		}
		catch (const std::exception&)
		{
			m_Records.clear();
			return false;  // 这一行坏了 → 整个文件判定为损坏
		}
	}
	return true;
}

void VideoStore::clear()
{
	m_Records.clear();
}

Time VideoStore::totalTimeAll() const
{
	Time total(0, 0, 0);
	for (const auto& r : m_Records)
	{
		total = total + r.getTime();
	}
	return total;
}


int VideoStore::indexOf(int collectionId, int partId, int serialId) const
{
	for (int i = 0; i < static_cast<int>(m_Records.size()); ++i)
	{
		if (m_Records[i].isAt(collectionId, partId, serialId))
		{
			return i;
		}
	}
	return -1;
}
