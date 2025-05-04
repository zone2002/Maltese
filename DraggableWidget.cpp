#include "DraggableWidget.h"
#include <QApplication>
#include <QCursor>

DraggableWidget::DraggableWidget(QWidget* parent)
    : QWidget(parent)
{
    // 无边框、透明背景
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // 安装事件过滤器
    installEventFilter(this);
}

bool DraggableWidget::eventFilter(QObject* obj, QEvent* event) {
    Q_UNUSED(obj);
    // 鼠标按下时记录偏移
    if (event->type() == QEvent::MouseButtonPress) {
        auto* me = static_cast<QMouseEvent*>(event);
        if (me->button() == Qt::LeftButton) {
            // pos() 是窗口当前位置
            dragPos_ = me->globalPosition().toPoint() - pos();
            return true;
        }
    }
    // 鼠标移动时根据偏移移动窗口
    else if (event->type() == QEvent::MouseMove) {
        auto* me = static_cast<QMouseEvent*>(event);
        if (me->buttons() & Qt::LeftButton) {
            move(me->globalPosition().toPoint() - dragPos_);
            return true;
        }
    }
    // 交给基类处理其他事件
    return QWidget::eventFilter(obj, event);
}
