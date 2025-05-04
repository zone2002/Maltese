#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QMap>
#include <QList>
#include <QUrl>
#include "RoleAct.h"

/// 资源管理器：负责维护 RoleAct 到帧资源路径列表的映射
class ResourceManager
{
public:
    /// 获取单例实例
    static ResourceManager& instance();

    /// 根据动画类型获取对应的帧列表
    QList<QUrl> framesFor(Act::RoleAct act) const;

private:
    ResourceManager();  ///< 私有构造函数，用于单例初始化
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    /// 工具：添加一组帧资源
    void addFrames(Act::RoleAct act, const QString& pattern, int count);
    // void addFrames(Act::RoleAct act, const QString& resourceDir);

    QMap<Act::RoleAct, QList<QUrl>> map_;  ///< 动画类型到帧列表的映射
};

#endif // RESOURCEMANAGER_H
