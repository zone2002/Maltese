#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QUrl>
#include <QTimer>

class QPaintEvent;

namespace Act {
    Q_NAMESPACE

enum RoleAct {
        Rolling,
        RideScooter,
        Bickering,
        MelodySprint,
        RideMaltese
    };
Q_ENUM_NS(RoleAct)

}

using namespace Act;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void showActAnimation(RoleAct act);

protected:
    void paintEvent(QPaintEvent* event)override;

private:
    QMap<RoleAct, QList<QUrl>> action_map;
    QTimer* timer;
    RoleAct cur_role_act;
    QUrl cur_role_pix;

private:
    void loadRoleActRes();
};

#endif // WIDGET_H
