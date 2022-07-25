#include "PhiObjCreate.h"

#include "../PhigrosObj/phinote.h"
#include "../PhigrosObj/phihold.h"
#include "../PhigrosObj/phijudgeline.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

PhiNote* createNote(
        PhiJudgeLine* jl,
        QString type    ,
        int     time    ,
        qreal   posX    ,
        qreal   speed   ,
        QString position,
        QObject* parent)
{
#ifdef QT_DEBUG
    qDebug() << "函数: CreateNote 开始";
#endif

    PhiNote* note = new PhiNote(parent);

#ifdef QT_DEBUG
    qDebug() << "创建PhiNote完成";
#endif

    note->setJudgeLine(jl);

#ifdef QT_DEBUG
    qDebug() << "设置judgeLine完成";
#endif

    note->setType(type);

#ifdef QT_DEBUG
    qDebug() << "设置种类完成";
#endif

    note->setTime(time);

#ifdef QT_DEBUG
    qDebug() << "设置被击打时间完成";
#endif

    note->setPosX(posX);

#ifdef QT_DEBUG
    qDebug() << "设置posX完成";
#endif

    note->setBasicSpeed(speed);

#ifdef QT_DEBUG
    qDebug() << "设置basicSpeed完成";
#endif

    note->setPosition(position);

#ifdef QT_DEBUG
    qDebug() << "设置上下面完成";
#endif

    note->initRFloorPostion();

#ifdef QT_DEBUG
    qDebug() << "设置判定线完成";
#endif

    jl->addNote_autoSort(note);
#ifdef QT_DEBUG
    qDebug() << "将Note插入判定线完成";
#endif
    return note;
}

PhiHold *createHold(
        PhiJudgeLine *jl,
        QString type,
        int time,
        int holdTime,
        qreal posX,
        qreal speed,
        QString position,
        QObject *parent)
{
#ifdef QT_DEBUG
    qDebug() << "函数: CreateHold 开始";
#endif

    Q_UNUSED(type)

    PhiHold* note = new PhiHold(parent);

#ifdef QT_DEBUG
    qDebug() << "创建PhiHold完成";
#endif

    note->setJudgeLine(jl);

#ifdef QT_DEBUG
    qDebug() << "设置judgeLine完成";
#endif

    note->setType("hold");

#ifdef QT_DEBUG
    qDebug() << "设置种类完成";
#endif

    note->setTime(time);

#ifdef QT_DEBUG
    qDebug() << "设置被击打时间完成";
#endif

    note->setHoldTime(holdTime);

#ifdef QT_DEBUG
    qDebug() << "设置按住时间完成";
#endif

    note->setPosX(posX);

#ifdef QT_DEBUG
    qDebug() << "设置posX完成";
#endif

    note->setBasicSpeed(speed);

#ifdef QT_DEBUG
    qDebug() << "设置basicSpeed完成";
#endif

    note->setPosition(position);

#ifdef QT_DEBUG
    qDebug() << "设置上下面完成";
#endif

    note->initRFloorPostion();

#ifdef QT_DEBUG
    qDebug() << "设置判定线完成";
#endif

    jl->addNote_autoSort(note);

#ifdef QT_DEBUG
    qDebug() << "将hold插入判定线完成";
#endif

    return note;
}
