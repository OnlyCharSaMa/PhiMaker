#include "phihitptc.h"

#include <QTimer>

#ifdef QT_DEBUG
#include <QDebug>
#endif

PhiHitPTC::PhiHitPTC(int ptcX,
                     int ptcY,
                     qreal rotate,
                     int xOffset,
                     int imgIndex,
                     QObject *parent
                     )
    : QObject{parent}
{
    // 进行基本赋值操作以免
    m_xOffset  = xOffset;
    m_rotate   = rotate;
    m_ptcX     = ptcX;
    m_ptcY     = ptcY;
    m_imgIndex = imgIndex;
    QTimer* timer = new QTimer(this);
    constexpr int interval = 1000 / 60;
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()),
            this,  SLOT(onTimeOut()));
    timer->start();
}

void PhiHitPTC::onTimeOut()
{
    if(m_imgIndex >= 29)
    {
        deleteLater();
        return;
    }

    emit requestHitPTC(m_ptcX, m_ptcY, m_rotate, m_xOffset, m_imgIndex);
    m_imgIndex++;

#ifdef QT_DEBUG
    qDebug() << "请求";
#endif
}

qreal PhiHitPTC::getRotate() const
{
    return m_rotate;
}

void PhiHitPTC::setRotate(qreal newRotate)
{
    m_rotate = newRotate;
}

int PhiHitPTC::getXOffset() const
{
    return m_xOffset;
}

void PhiHitPTC::setXOffset(int newXOffset)
{
    m_xOffset = newXOffset;
}

int PhiHitPTC::ptcY() const
{
    return m_ptcY;
}

void PhiHitPTC::setPtcY(int newPtcY)
{
    m_ptcY = newPtcY;
}



int PhiHitPTC::ptcX() const
{
    return m_ptcX;
}

void PhiHitPTC::setPtcX(int newPtcX)
{
    m_ptcX = newPtcX;
}
