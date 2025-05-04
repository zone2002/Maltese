#include "AppController.h"
#include "AnimatedWidget.h"        // ← 添加完整定义
#include "TrayMenuBuilder.h"

#include <QSystemTrayIcon>
#include <QApplication>
#include <QMessageBox>
#include <QIcon>

AppController::AppController(QObject* parent)
    : QObject(parent),
    trayIcon_(nullptr),
    mainWidget_(nullptr)
{}

int AppController::run(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 1. 系统托盘可用性检查
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr,
                              tr("错误"),
                              tr("系统托盘不可用，应用无法启动。"));
        return -1;
    }

    // 2. 应用名称和图标
    app.setApplicationName("MyAnimatedApp");
    app.setWindowIcon(QIcon(":/img/icon.png"));

    // 3. 创建并配置主窗口
    mainWidget_ = new AnimatedWidget;
    mainWidget_->setWindowTitle(tr("动画小部件"));

    // 4. 创建系统托盘图标（QIcon, QObject*）
    trayIcon_ = new QSystemTrayIcon(QIcon(":/img/icon.png"), mainWidget_);
    trayIcon_->setToolTip(tr("MyAnimatedApp - 动画演示"));
    trayIcon_->setContextMenu(menuBuilder_.buildMenu(mainWidget_));
    trayIcon_->show();

    // 5. 连接菜单动作到动画切换
    connect(&menuBuilder_, &TrayMenuBuilder::actionSelected,
            mainWidget_,
            [this](int actValue) {
                mainWidget_->showAnimation(
                    static_cast<Act::RoleAct>(actValue)
                    );
            });

    // 6. 显示主窗口
    mainWidget_->show();

    return app.exec();
}
