#ifndef ANIMATEDWIDGET_H
#define ANIMATEDWIDGET_H

#include "DraggableWidget.h"
#include "RoleAct.h"
#include "AnimationController.h"

#include <QUrl>

class AnimatedWidget : public DraggableWidget
{
    Q_OBJECT

public:
    explicit AnimatedWidget(QWidget* parent = nullptr);

    /// 切换并显示指定动作的动画
    void showAnimation(Act::RoleAct act);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    /// 接收每帧更新信号
    void updateFrame(const QUrl& pix);

private:
    AnimationController animCtrl_;  ///< 动画控制器，负责定时发帧
    QUrl              currentPix_;  ///< 当前要绘制的帧图片路径
};

#endif // ANIMATEDWIDGET_H
