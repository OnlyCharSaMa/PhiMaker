#ifndef PHINOTE_H
#define PHINOTE_H

#include "phiabstractnote.h"
#include "../classesDeclaration.h"
#include <QObject>


class PhiNote : public PhiAbstractNote
{
    Q_OBJECT
public:
    explicit PhiNote(QObject *parent = nullptr);

public slots:
    void checkTime(); // check the time and make sure the status is right
    void crash();

private:


signals:


};

#endif // PHINOTE_H
