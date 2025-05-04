#include "ResourceManager.h"
#include <QString>
#include <QDebug>
#include <QDir>

ResourceManager& ResourceManager::instance()
{
    static ResourceManager mgr;
    return mgr;
}

ResourceManager::ResourceManager()
{
    // 在这里集中定义所有 RoleAct 的资源路径
    addFrames(Act::RoleAct::Rolling,       ":/img/rolling/rolling_%1.png",        20);
    addFrames(Act::RoleAct::RideScooter,   ":/img/ride_scooter/ride_scooter_%1.png", 12);
    addFrames(Act::RoleAct::RideMaltese,   ":/img/ride_maltese/ride_maltese_%1.png", 6);
    addFrames(Act::RoleAct::Bickering,     ":/img/bickering/bickering_%1.png",     8);
    addFrames(Act::RoleAct::MelodySprint,  ":/img/melody_sprint/melody_sprint_%1.png", 11);
}

// ResourceManager::ResourceManager()
// {
//     addFrames(Act::RoleAct::Rolling,      ":/img/rolling");
//     addFrames(Act::RoleAct::RideScooter,  ":/img/ride_scooter");
//     addFrames(Act::RoleAct::RideMaltese,  ":/img/ride_maltese");
//     addFrames(Act::RoleAct::Bickering,    ":/img/bickering");
//     addFrames(Act::RoleAct::MelodySprint, ":/img/melody_sprint");
// }


// void ResourceManager::addFrames(Act::RoleAct act, const QString &resourceDir)
// {
//     QDir dir(resourceDir);
//     QStringList fileNames = dir.entryList(QDir::Files, QDir::Name); // 按名称排序
//     QList<QUrl> list;
//     for (const QString& fileName : fileNames) {
//         list.append(QUrl("qrc" + resourceDir + "/" + fileName));
//     }
//     map_.insert(act, list);
// }

void ResourceManager::addFrames(Act::RoleAct act, const QString& pattern, int count)
{
    QList<QUrl> list;
    for (int i = 0; i < count; ++i) {
        // 使用 QString::arg 来格式化文件名
        QString path = pattern.arg(i);
        QUrl url = QUrl::fromLocalFile(path);
        list.append(url);
    }
    map_.insert(act, list);
}

QList<QUrl> ResourceManager::framesFor(Act::RoleAct act) const
{
    // 如果找不到会返回一个空的 QList
    return map_.value(act);
}
