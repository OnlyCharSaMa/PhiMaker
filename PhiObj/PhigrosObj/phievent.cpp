#include "phievent.h"

PhiEvent::PhiEvent(QObject *parent)
    : QObject{parent}
{

}

int PhiEvent::startTime() const
{
    return m_startTime;
}

void PhiEvent::setStartTime(int newStartTime)
{
    m_startTime = newStartTime;
}

int PhiEvent::endTime() const
{
    return m_endTime;
}

void PhiEvent::setEndTime(int newEndTime)
{
    m_endTime = newEndTime;
}

const QVariant &PhiEvent::start() const
{
    return m_start;
}

void PhiEvent::setStart(const QVariant &newStart)
{
    m_start = newStart;
}

const QVariant &PhiEvent::end() const
{
    return m_end;
}

void PhiEvent::setEnd(const QVariant &newEnd)
{
    m_end = newEnd;
}

int PhiEvent::easingType() const
{
    return m_easingType;
}

void PhiEvent::setEasingType(int newEasingType)
{
    m_easingType = newEasingType;
}

qreal PhiEvent::easingAmplitude() const
{
    return m_easingAmplitude;
}

void PhiEvent::setEasingAmplitude(qreal newEasingAmplitude)
{
    m_easingAmplitude = newEasingAmplitude;
}

qreal PhiEvent::easingOvershoot() const
{
    return m_easingOvershoot;
}

void PhiEvent::setEasingOvershoot(qreal newEasingOvershoot)
{
    m_easingOvershoot = newEasingOvershoot;
}

qreal PhiEvent::easingPeriod() const
{
    return m_easingPeriod;
}

void PhiEvent::setEasingPeriod(qreal newEasingPeriod)
{
    m_easingPeriod = newEasingPeriod;
}

const BezierCurveData &PhiEvent::bezirCurveData() const
{
    return m_bezirCurveData;
}

void PhiEvent::setBezirCurveData(const BezierCurveData &newBezirCurveData)
{
    m_bezirCurveData = newBezirCurveData;
}

QEasingCurve PhiEvent::getCurve()
{
    QEasingCurve curve;
    curve.setType(QEasingCurve::Type(m_easingType));
    curve.setAmplitude(m_easingAmplitude);
    curve.setOvershoot(m_easingOvershoot);
    curve.setPeriod(m_easingPeriod);
    if(m_easingType == QEasingCurve::BezierSpline)
    {
        curve.addCubicBezierSegment(m_bezirCurveData.c1,
                                    m_bezirCurveData.c2,
                                    m_bezirCurveData.endPoint);
    }
    return curve;
}




