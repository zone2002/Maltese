#include "TrayMenuBuilder.h"
#include "RoleAct.h"

#include <QAction>
#include <QMetaEnum>
#include <QApplication>

TrayMenuBuilder::TrayMenuBuilder(QObject* parent)
    : QObject(parent)
{}

QMenu* TrayMenuBuilder::buildMenu(QWidget* receiver)
{
    QMenu* menu = new QMenu(receiver);
    addRoleActions(menu);
    menu->addSeparator();
    addCommonActions(menu, receiver);
    return menu;
}

void TrayMenuBuilder::addRoleActions(QMenu* menu)
{
    // 通过 Qt 元对象系统枚举所有 RoleAct 键
    const QMetaObject& mo = Act::staticMetaObject;
    int idx = mo.indexOfEnumerator("RoleAct");
    QMetaEnum me = mo.enumerator(idx);

    for (int i = 0; i < me.keyCount(); ++i) {
        const char* key = me.key(i);
        int value = me.value(i);
        QAction* act = new QAction(QString::fromLatin1(key), menu);
        act->setData(value);
        connect(act, &QAction::triggered, this, [this, value]() {
            emit actionSelected(value);
        });
        menu->addAction(act);
    }
}

void TrayMenuBuilder::addCommonActions(QMenu* menu, QWidget* receiver)
{
    // “显示” 窗口
    QAction* showAct = new QAction(tr("Show"), menu);
    connect(showAct, &QAction::triggered, receiver, [receiver]() {
        receiver->setVisible(true);
    });
    menu->addAction(showAct);

    // “隐藏” 窗口
    QAction* hideAct = new QAction(tr("Hide"), menu);
    connect(hideAct, &QAction::triggered, receiver, [receiver]() {
        receiver->setVisible(false);
    });
    menu->addAction(hideAct);

    // 退出应用
    QAction* exitAct = new QAction(tr("Exit"), menu);
    connect(exitAct, &QAction::triggered, qApp, &QApplication::quit);
    menu->addAction(exitAct);
}
