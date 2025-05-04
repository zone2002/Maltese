// 应用程序入口及系统托盘管理
#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "TrayMenuBuilder.h"
class QSystemTrayIcon;
class AnimatedWidget;

class AppController : public QObject
{
    Q_OBJECT

public:
    explicit AppController(QObject* parent = nullptr);
    int run(int argc, char* argv[]);

private:
    QSystemTrayIcon* trayIcon_       = nullptr;   // 系统托盘图标
    AnimatedWidget*  mainWidget_     = nullptr;   // 主窗口（动画窗口）
    TrayMenuBuilder  menuBuilder_;                // 菜单构造器
};

#endif // APPCONTROLLER_H
