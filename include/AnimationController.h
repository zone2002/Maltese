// 控制帧动画的计时器与更新
#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QList>

#include "RoleAct.h"

class AnimationController : public QObject
{
    Q_OBJECT

public:
    explicit AnimationController(QObject *parent = nullptr);

    /// 开始播放指定动作的动画
    void start(Act::RoleAct act);

    /// 停止当前动画
    void stop();

signals:
    /// 每次定时器超时后发出，携带当前要显示的帧路径
    void frameReady(const QUrl& frame);

private slots:
    /// 定时器回调，用于切换到下一帧并 emit frameReady
    void onTimeout();

private:
    QTimer*        timer_         = nullptr;  ///< 定时器
    QList<QUrl>    currentFrames_;            ///< 当前动作对应的所有帧
    int            currentIndex_  = 0;        ///< 当前帧索引
};

#endif // ANIMATIONCONTROLLER_H
