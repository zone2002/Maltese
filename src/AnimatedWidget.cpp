#include "AnimatedWidget.h"

#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>

AnimatedWidget::AnimatedWidget(QWidget* parent)
    : DraggableWidget(parent)
    , animCtrl_(this)
{
    // 窗口无边框、透明背景已由 DraggableWidget 处理

    // 连接动画控制器的每帧信号到本类的槽
    connect(&animCtrl_, &AnimationController::frameReady,
            this, &AnimatedWidget::updateFrame);

    // 默认启动 Rolling 动画
    showAnimation(Act::RoleAct::Rolling);
}

void AnimatedWidget::showAnimation(Act::RoleAct act)
{
    // 停止当前动画（内部会重置计时器和索引）
    animCtrl_.start(act);
}

void AnimatedWidget::updateFrame(const QUrl& pix)
{
    // 收到新帧，保存路径并触发重绘
    currentPix_ = pix;
    update();  // 调用 paintEvent
}

void AnimatedWidget::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);

    // 如果尚未收到任何帧，则不绘制
    if (currentPix_.isEmpty())
        return;

    // 加载并绘制当前帧到窗口
    QPixmap pix;
    pix.load(currentPix_.toLocalFile());
    painter.drawPixmap(0, 0, pix);
}
