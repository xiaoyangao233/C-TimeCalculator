#include"VideoStore.h"

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
			total = r.getTime() + total;
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
