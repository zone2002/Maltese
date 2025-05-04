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
    addFrames(Act::RoleAct::Rolling,      ":/img/rolling/rolling_%1.png");
    addFrames(Act::RoleAct::RideScooter,  ":/img/ride_scooter/ride_scooter_%1.png");
    addFrames(Act::RoleAct::RideMaltese,  ":/img/ride_maltese/ride_maltese_%1.png");
    addFrames(Act::RoleAct::Bickering,    ":/img/bickering/bickering_%1.png");
    addFrames(Act::RoleAct::MelodySprint, ":/img/melody_sprint/melody_sprint_%1.png");
}


void ResourceManager::addFrames(Act::RoleAct act, const QString& pattern)
{
    QList<QUrl> list;
    int count = 0;

    while (true) {
        QString path = pattern.arg(count);
        // 使用Qt资源系统专用检测方式
        if (QFile::exists(path)) {
            list.append(QUrl::fromLocalFile(path));
            count++;
        } else {
            if (count == 0) {
                qWarning() << "Missing frames:" << path;
            }
            break;
        }
    }

    map_.insert(act, list);
}

QList<QUrl> ResourceManager::framesFor(Act::RoleAct act) const
{
    // 如果找不到会返回一个空的 QList
    return map_.value(act);
}
