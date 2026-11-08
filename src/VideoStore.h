#pragma once
#include<vector>
#include "VideoRecord.h"
#include<string>

class VideoStore
{
public:

    // 添加一条记录。已存在相同 (合集, 部分, 序号) 时返回 false，容器不变。
    bool add(const VideoRecord& r);

    // 删除指定编号的记录。找不到返回 false。
    bool remove(int collectionId, int partId, int serialId);

    // 修改指定编号的记录。整条修改
    // 找不到或者重复（不包含自己）返回false
    bool modify(int collectionId, int partId, int serialId, const VideoRecord& r);

    // 按编号查找。找到返回指向该记录的指针，找不到返回 nullptr。
    // 注意：指针在下一次 add / remove 之后可能失效，不要长期保存。
    const VideoRecord* find(int collectionId, int partId, int serialId) const;

    // 返回全部记录的只读引用。
    // 注意：该引用在下一次 add / remove 之后可能失效，不要长期保存。
    const std::vector<VideoRecord>& all() const;

    //返回这个部分或合集的总时长。无记录时，返回00:00:00
    Time totalTimeOfPart(int collectionId, int partId) const;
    Time totalTimeOfCollection(int collectionId) const;

    //清空所有信息
    void clear();

    //计算所有视频总时长
    Time totalTimeAll() const;

    // ===== 文件 =====
    // 从文件加载记录。成功返回 true。文件不存在或内容损坏返回 false。
    bool loadFrom(const std::string& path);

    // 把全部记录写入文件。成功返回 true。
    bool saveTo(const std::string& path) const;

private:
    // 按编号定位，返回下标；找不到返回 -1。
    // 所有增删改查都经由它，保证"什么算同一条记录"只有一处定义
    int indexOf(int collectionId, int partId, int serialId) const;

    std::vector<VideoRecord> m_Records;

};