#include "phihold.h"
#include "../Widgets/phiviewer.h"

PhiHold::PhiHold(QObject *parent)
    : PhiAbstractNote{parent}
{
    // 初始化成员
    m_ptcTimer.setInterval(333);

    // 连接信号与槽
    connect(this, &PhiAbstractNote::timeChanged,
            [=](){setEndTime(time() + holdTime());}); // 设置彻底结束的时间

    connect(this, &PhiHold::holdTimeChanged,
            [=](){setEndTime(time() + holdTime());}); // 设置彻底结束的时间

    connect(&m_ptcTimer, &QTimer::timeout,
            [=](){setRequestPTC(true);});             // 当timer时间到了请求打击特效
}

void PhiHold::checkTime()
{
    if( (time() + holdTime() - phiViewer()->currentTime()) <= 0 && !isCrashed() && isCompleted())
    {
        crash();
    }
    else if( ((time() - phiViewer()->currentTime()) < 0) && ((time() + holdTime() - phiViewer()->currentTime()) > 0))
    {
        if(m_anmFinishedTime == 0)
        {
            setRequestSound(true);
            setRequestPTC(true);  // QTimer 好像没有TrrigerOnStart(刚开始时就就发送信号）这里手动触发一次
            m_ptcTimer.start();
            m_anmFinishedTime++;
        }
    }
    else if( (time() - phiViewer()->currentTime()) >= 0 && isCrashed())
    {
        setIsCrashed(false);
    }
}

void PhiHold::crash()
{
    emit crashed();
    m_ptcTimer.stop();
    setIsCrashed(true);
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


