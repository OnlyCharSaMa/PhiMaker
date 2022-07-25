#ifndef PHIOBJCREATE_H
#define PHIOBJCREATE_H

#include "../classesDeclaration.h"
#include <QObject>
#include <QString>

PhiNote* createNote(
        PhiJudgeLine* jl = nullptr,
        QString type     = "tap",
        int     time     = 1000,
        qreal   posX     = 0,
        qreal   speed    = 0.3,
        QString position = "above",
        QObject* parent  = nullptr);

PhiHold* createHold(
        PhiJudgeLine* jl = nullptr,
        QString type     = "114514", // 这只是用来提醒自己，这个函数type其实就是凑数的，为了与上面的函数统一qwq
        int     time     = 1000,
        int     holdTime = 1000,
        qreal   posX     = 0,
        qreal   speed    = 0.3,
        QString position = "above",
        QObject* parent  = nullptr);


#endif // PHIOBJCREATE_H
