#ifndef PHIHOLD_H
#define PHIHOLD_H

#include "phiabstractnote.h"

class PhiHold : public PhiAbstractNote
{
    Q_OBJECT
    Q_PROPERTY(int holdTime READ holdTime WRITE setHoldTime NOTIFY holdTimeChanged)
public:
    explicit PhiHold(QObject *parent = nullptr);



    int holdTime() const;
    void setHoldTime(int newHoldTime);

private:
    int m_holdTime;

signals:
    void holdTimeChanged();



};

#endif // PHIHOLD_H
