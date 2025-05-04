#ifndef DRAGGABLEWIDGET_H
#define DRAGGABLEWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>

class DraggableWidget : public QWidget {
    Q_OBJECT
public:
    explicit DraggableWidget(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QPoint dragPos_;  // 用于记录拖拽偏移
};

#endif // DRAGGABLEWIDGET_H
