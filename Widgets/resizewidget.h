#ifndef RESIZEWIDGET_H
#define RESIZEWIDGET_H

#include <QWidget>

class ResizeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResizeWidget(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event);
signals:
    void resized(const QSize&);
};

#endif // RESIZEWIDGET_H
