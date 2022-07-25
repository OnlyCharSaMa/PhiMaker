#ifndef PHIEVENT_H
#define PHIEVENT_H

#include <QEasingCurve>
#include <QPointF>
#include <QVariant>
#include <QObject>

struct BezierCurveData
{
    QPointF c1;
    QPointF c2;
    QPointF endPoint;
};

class PhiEvent : public QObject
{
    Q_OBJECT
public:
    explicit PhiEvent(QObject *parent = nullptr);

    int startTime() const;
    void setStartTime(int newStartTime);

    int endTime() const;
    void setEndTime(int newEndTime);

    const QVariant &start() const;
    void setStart(const QVariant &newStart);

    const QVariant &end() const;
    void setEnd(const QVariant &newEnd);

    int easingType() const;
    void setEasingType(int newEasingType);

    qreal easingAmplitude() const;
    void setEasingAmplitude(qreal newEasingAmplitude);

    qreal easingOvershoot() const;
    void setEasingOvershoot(qreal newEasingOvershoot);

    qreal easingPeriod() const;
    void setEasingPeriod(qreal newEasingPeriod);

    const BezierCurveData &bezirCurveData() const;
    void setBezirCurveData(const BezierCurveData &newBezirCurveData);

public:
    QEasingCurve getCurve();

private:
    int             m_startTime;
    int             m_endTime;
    QVariant        m_start;
    QVariant        m_end;
    int             m_easingType = QEasingCurve::Linear;
    qreal           m_easingAmplitude;
    qreal           m_easingOvershoot;
    qreal           m_easingPeriod;
    BezierCurveData m_bezirCurveData;

signals:

};

#endif // PHIEVENT_H
