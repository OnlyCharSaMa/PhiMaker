#include "phihold.h"

PhiHold::PhiHold(QObject *parent)
    : PhiAbstractNote{parent}
{
    connect(this, &PhiAbstractNote::timeChanged,
            [=](){setEndTime(time() + holdTime());}); // 设置彻底结束的时间

    connect(this, &PhiHold::holdTimeChanged,
            [=](){setEndTime(time() + holdTime());}); // 设置彻底结束的时间
}

int PhiHold::holdTime() const
{
    return m_holdTime;
}

void PhiHold::setHoldTime(int newHoldTime)
{
    if (m_holdTime == newHoldTime)
        return;
    m_holdTime = newHoldTime;
    emit holdTimeChanged();
}


