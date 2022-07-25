#include "Math2d.h"

qreal angleToArc(qreal angle)
{
    return 3.14159 * angle / 180;
}

QPoint getLineCenter(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QPoint p;
    p.setX(static_cast<int>( (x1 + x2) / 2) );
    p.setY(static_cast<int>( (y1 + y2) / 2) );
    return p;
}

QPoint centerToLeftTop(qreal x, qreal y, qreal w, qreal h)
{
    QPoint p;
    p.setX(static_cast<int>(x - (w / 2) ));
    p.setY(static_cast<int>(y - (h / 2) ));
    return p;
}

QPoint leftTopToCenter(qreal x, qreal y, qreal w, qreal h)
{
    QPoint p;
    p.setX(static_cast<int>(x + (w / 2) ));
    p.setY(static_cast<int>(y + (y / 2) ));
    return p;
}
