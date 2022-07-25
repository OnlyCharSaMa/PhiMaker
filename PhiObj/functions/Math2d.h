#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QObject>
#include <QPoint>

qreal angleToArc(qreal angle);
QPoint getLineCenter(qreal x1, qreal y1, qreal x2, qreal y2);
QPoint centerToLeftTop(qreal x, qreal y, qreal w, qreal h);
QPoint leftTopToCenter(qreal x, qreal y, qreal w, qreal h);

#endif // FUNCTIONS_H
