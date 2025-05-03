#include "widget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    timer(new QTimer(this))
{
    connect(timer, &QTimer::timeout, [this]() {
        static int index = 0;
        auto paths = this->action_map.value(this->cur_role_act);
        this->cur_role_pix = paths[index % paths.size()];
        index++;
        this->update();
    });

    loadRoleActRes();

    showActAnimation(RoleAct::Rolling);
}

Widget::~Widget() {}

void Widget::showActAnimation(RoleAct act)
{
    timer->stop();
    this->cur_role_act = act;
    timer->start(60);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix_map;
    pix_map.load(this->cur_role_pix.toLocalFile());

    painter.drawPixmap(0, 0, pix_map);
}

void Widget::loadRoleActRes()
{
    auto addRes = [this](RoleAct act, QString path, int count) {
        QList<QUrl> paths;
        char buf[255];
        for (int i = 0; i < count; ++i) {
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, path.toStdString().c_str(), i);
            paths.append(QUrl::fromLocalFile(buf));
        }
        action_map.insert(act, paths);
    };

    //todo
    addRes(RoleAct::Rolling, ":/img/rolling/rolling_%d.png", 20);
    addRes(RoleAct::RideScooter, ":/img/ride_scooter/ride_scooter_%d.png", 12);
    addRes(RoleAct::RideMaltese, ":/img/ride_maltese/ride_maltese_%d.png", 6);
    addRes(RoleAct::Bickering, ":/img/bickering/bickering_%d.png", 8);
    addRes(RoleAct::MelodySprint, ":/img/melody_sprint/melody_sprint_%d.png", 11);

}
