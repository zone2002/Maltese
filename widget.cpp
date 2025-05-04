#include "widget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QCursor>
#include <QMetaEnum>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    timer(new QTimer(this)),
    menu(new QMenu(this))
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->installEventFilter(new DragFilter);

    connect(timer, &QTimer::timeout, [this]() {
        static int index = 0;
        auto paths = this->action_map.value(this->cur_role_act);
        this->cur_role_pix = paths[index % paths.size()];
        index++;
        this->update();
    });

    initMenu();

    loadRoleActRes();

    showActAnimation(RoleAct::Rolling);
}

Widget::~Widget() {}

void Widget::onMenuTriggered(QAction *action)
{
    QMetaEnum me = QMetaEnum::fromType<RoleAct>();
    bool ok;
    int k = me.keyToValue(action->text().toStdString().c_str(), &ok);
    if (!ok) {
        return;
    }

    showActAnimation(static_cast<RoleAct>(k));
}

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

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    this->menu->popup(QCursor::pos());
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

void Widget::initMenu()
{
    menu->addAction("Rolling");
    menu->addAction("RideScooter");
    menu->addAction("RideMaltese");
    menu->addAction("Bickering");
    menu->addAction("MelodySprint");

    QAction* act = new QAction("Hide");
    connect(act, &QAction::triggered, [this](){
        this->setVisible(false);
    });
    menu->addAction(act);

    connect(this->menu, &QMenu::triggered, this, &Widget::onMenuTriggered);
}
