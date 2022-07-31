#include "phiabstractnote.h"
#include "phijudgeline.h"
#include "../Widgets/phiviewer.h"

#include <QDebug>
#ifdef QT_DEBUG
#include <QDebug>
#endif


PhiAbstractNote::PhiAbstractNote(QObject *parent)
    : QObject{parent}
{

#ifdef QT_DEBUG
    qDebug() << "note抽象类的初始化开始";
#endif



    // 初始化 rFloorPos
    m_isCompleted = true;

    // 连接


#ifdef QT_DEBUG
    qDebug() << "note抽象类的初始化结束";
#endif
}

void PhiAbstractNote::checkTypeIndex()
{
    if(m_type == "tap"){m_typeIndex = 0;}
    else if(m_type == "drag"){m_typeIndex = 1;}
    else if(m_type == "flick"){m_typeIndex = 2;}
    else if(m_type == "hold"){m_typeIndex = 3;}
    else
    {
#ifdef QT_DEBUG
        qDebug() << "完成了单个判定线的绘制";
#endif
        m_typeIndex = 0;
        m_type      = "tap";
    }
    checkHighLight();
}



void PhiAbstractNote::updateRFloorPostion()
{
    // 用速度和时间计算出rFloorPostion
    initSpeed();
    m_rFloorPos = (m_time - m_phiViewer->currentTime()) * m_speed / 1000;
#ifdef QT_DEBUG
    qDebug() << "m_time: " << m_time;
    qDebug() << "currentTime: " << m_phiViewer->currentTime();
    qDebug() << "m_speed: " << m_speed;
#endif
}

void PhiAbstractNote::initRFloorPostion()
{
    m_rFloorPos = m_time * m_speed / 1000;
}

void PhiAbstractNote::initSpeed()
{
    setSpeed(m_basicSpeed + m_judgeLine->speed());
}

void PhiAbstractNote::checkTime()
{

}

void PhiAbstractNote::crash()
{

}

int PhiAbstractNote::endTime() const
{
    return m_endTime;
}

void PhiAbstractNote::setEndTime(int newEndTime)
{
    m_endTime = newEndTime;
#ifdef QT_DEBUG
    qDebug() << "设置了endTime: " << newEndTime;
#endif
}


PhiJudgeLine *PhiAbstractNote::judgeLine() const
{
    return m_judgeLine;
}

void PhiAbstractNote::setJudgeLine(PhiJudgeLine *newJudgeLine)
{
    if (m_judgeLine == newJudgeLine)
        return;
    m_judgeLine = newJudgeLine;
    emit judgeLineChanged();

    setPhiViewer(newJudgeLine->phiViewer());
}

PhiViewer *PhiAbstractNote::phiViewer() const
{
    return m_phiViewer;
}

void PhiAbstractNote::setPhiViewer(PhiViewer *newPhiViewer)
{
    if (m_phiViewer == newPhiViewer)
        return;
    m_phiViewer = newPhiViewer;
    emit phiViewerChanged();

    connect(this,                  SIGNAL(requestedSound(int)),
            m_phiViewer->player(), SLOT(play(int)));
}


// setter and getter

void PhiAbstractNote::checkHighLight()
{
    if(m_highLight){m_typeIndex += 4;}
}

bool PhiAbstractNote::highLight() const
{
    return m_highLight;
}

void PhiAbstractNote::setHighLight(bool newHighLight)
{
    if (m_highLight == newHighLight)
        return;
    m_highLight = newHighLight;
    emit highLightChanged();

    checkHighLight();
}

const QString &PhiAbstractNote::type() const
{
    return m_type;
}

void PhiAbstractNote::setType(const QString &newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();

    checkTypeIndex();
}

int PhiAbstractNote::typeIndex() const
{
    return m_typeIndex;
}

void PhiAbstractNote::setTypeIndex(int newTypeIndex)
{
    if (m_typeIndex == newTypeIndex)
        return;
    m_typeIndex = newTypeIndex;
    emit typeIndexChanged();
}

qreal PhiAbstractNote::posX() const
{
    return m_posX;
}

void PhiAbstractNote::setPosX(qreal newPosX)
{
    if (qFuzzyCompare(m_posX, newPosX))
        return;
    m_posX = newPosX;
    emit posXChanged();
}

qreal PhiAbstractNote::rFloorPos() const
{
    return m_rFloorPos;
}

void PhiAbstractNote::setRFloorPos(qreal newRFloorPos)
{
    m_rFloorPos = newRFloorPos;
}

qreal PhiAbstractNote::speed() const
{
    return m_speed;
}

void PhiAbstractNote::setSpeed(qreal newSpeed)
{
    if (qFuzzyCompare(m_speed, newSpeed))
        return;
    m_speed = newSpeed;
    emit speedChanged();

    initRFloorPostion();

}

qreal PhiAbstractNote::basicSpeed() const
{
    return m_basicSpeed;
}

void PhiAbstractNote::setBasicSpeed(qreal newBasicSpeed)
{
    if (qFuzzyCompare(m_basicSpeed, newBasicSpeed))
        return;
    m_basicSpeed = newBasicSpeed;
    emit basicSpeedChanged();

    initSpeed();

}

qreal PhiAbstractNote::time() const
{
    return m_time;
}

void PhiAbstractNote::setTime(qreal newTime)
{
    if (qFuzzyCompare(m_time, newTime))
        return;
    m_time = newTime;
    emit timeChanged();

    initRFloorPostion();
}

const QString &PhiAbstractNote::position() const
{
    return m_position;
}

void PhiAbstractNote::setPosition(const QString &newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    emit positionChanged();
}


bool PhiAbstractNote::requestSound() const
{
    return m_requestSound;
}

void PhiAbstractNote::setRequestSound(bool requsetSound)
{
    if (m_requestSound == requsetSound)
        return;
    m_requestSound = requsetSound;
    emit requestSoundChanged();

#ifdef QT_DEBUG
    if(m_phiViewer == nullptr){qDebug() << "播放打击音效失败，因为note里的phiViewer指针是空的,noteIndex: " << m_typeIndex;}
#endif
    if(m_requestSound == true)
    {emit requestedSound(m_typeIndex);}
    m_requestSound = false;
}

bool PhiAbstractNote::RequestPTC() const
{
    return m_requestPTC;
}

void PhiAbstractNote::setRequestPTC(bool newRequestPTC)
{
    if (m_requestPTC == newRequestPTC)
        return;
    m_requestPTC = newRequestPTC;
    emit requestPTCChanged();
}

bool PhiAbstractNote::isCrashed() const
{
    return m_isCrashed;
}

void PhiAbstractNote::setIsCrashed(bool newIsCrashed)
{
    m_isCrashed = newIsCrashed;
}

bool PhiAbstractNote::isDestoried() const
{
    return m_isDestoried;
}

void PhiAbstractNote::setIsDestoried(bool newIsDestoried)
{
    m_isDestoried = newIsDestoried;
}

bool PhiAbstractNote::isCompleted() const
{
    return m_isCompleted;
}

void PhiAbstractNote::setIsCompleted(bool newIsCompleted)
{
    m_isCompleted = newIsCompleted;
}


