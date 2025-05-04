#include "AnimationController.h"
#include "ResourceManager.h"

AnimationController::AnimationController(QObject *parent)
    : QObject(parent),
    timer_(new QTimer(this))
{
    connect(timer_, &QTimer::timeout,
            this, &AnimationController::onTimeout);
}

void AnimationController::start(Act::RoleAct act)
{
    stop();
    currentFrames_ = ResourceManager::instance().framesFor(act);
    if (currentFrames_.isEmpty()) return;
    currentIndex_ = 0;
    timer_->start(60);
}

void AnimationController::stop()
{
    if (timer_->isActive()) timer_->stop();
    currentFrames_.clear();
    currentIndex_ = 0;
}

void AnimationController::onTimeout()
{
    if (currentFrames_.isEmpty()) return;
    const QUrl& frame = currentFrames_.at(currentIndex_ % currentFrames_.size());
    ++currentIndex_;
    emit frameReady(frame);
}
