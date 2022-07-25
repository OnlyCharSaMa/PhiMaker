#ifndef PHIHOLD_H
#define PHIHOLD_H

#include "phiabstractnote.h"
#include <QTimer>

class PhiHold : public PhiAbstractNote
{
    Q_OBJECT
    Q_PROPERTY(int holdTime READ holdTime WRITE setHoldTime NOTIFY holdTimeChanged)
public:
    explicit PhiHold(QObject *parent = nullptr);

public:
    void checkTime();
    void crash();

public:
    int holdTime() const;
    void setHoldTime(int newHoldTime);

private:
    // 属性一类的
    int m_holdTime;
    int m_anmFinishedTime = 0;

    // 成员
    QTimer m_ptcTimer;

signals:
    void holdTimeChanged();



};

#endif // PHIHOLD_H
