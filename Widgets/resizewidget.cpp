#include "resizewidget.h"
#include <QResizeEvent>

#ifdef QT_DEBUG
#include <QDebug>
#endif

ResizeWidget::ResizeWidget(QWidget *parent)
    : QWidget{parent}
{

}

void ResizeWidget::resizeEvent(QResizeEvent *event)
{
    emit resized(event->size());

#ifdef QT_DEBUG
    qDebug() << "resizeWidget重设了大小."
             << " 宽为: " << event->size().width()
             << " 高为: " << event->size().height();
#endif
}
