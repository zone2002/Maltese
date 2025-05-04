#ifndef TRAYMENUBUILDER_H
#define TRAYMENUBUILDER_H

#include <QObject>
#include <QMenu>

class TrayMenuBuilder : public QObject
{
    Q_OBJECT
public:
    explicit TrayMenuBuilder(QObject* parent = nullptr);

    /// 根据枚举自动添加动作项，并附加通用的 Show/Hide/Exit
    QMenu* buildMenu(QWidget* receiver);

signals:
    /// 当用户选择某个动画动作时发射
    void actionSelected(int roleActValue);

private:
    void addRoleActions(QMenu* menu);
    void addCommonActions(QMenu* menu, QWidget* receiver);
};

#endif // TRAYMENUBUILDER_H
