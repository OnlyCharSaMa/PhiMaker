#ifndef PHIABSTRACTNOTE_H
#define PHIABSTRACTNOTE_H

#include "../classesDeclaration.h"
#include <QObject>

class PhiAbstractNote : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int typeIndex READ typeIndex WRITE setTypeIndex NOTIFY typeIndexChanged)
    Q_PROPERTY(qreal posX READ posX WRITE setPosX NOTIFY posXChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qreal basicSpeed READ basicSpeed WRITE setBasicSpeed NOTIFY basicSpeedChanged)
    Q_PROPERTY(qreal time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(PhiViewer *phiViewer READ phiViewer WRITE setPhiViewer NOTIFY phiViewerChanged)
    Q_PROPERTY(PhiJudgeLine *judgeLine READ judgeLine WRITE setJudgeLine NOTIFY judgeLineChanged)

    enum Type { Tap, Drag, Flick, Hold };
public:
    explicit PhiAbstractNote(QObject *parent = nullptr);

    // basic info
    const QString &type() const;
    void setType(const QString &newType);

    int typeIndex() const;
    void setTypeIndex(int newTypeIndex);

    bool highLight() const;
    void setHighLight(bool newHighLight);

    qreal posX() const;
    void setPosX(qreal newPosX);

    qreal rFloorPos() const;
    void setRFloorPos(qreal newRFloorPos);

    qreal speed() const;
    void setSpeed(qreal newSpeed);

    qreal basicSpeed() const;
    void setBasicSpeed(qreal newBasicSpeed);

    qreal time() const;
    void setTime(qreal newTime);

    const QString &position() const;
    void setPosition(const QString &newPosition);

    bool RequestPTC() const;
    void setRequestPTC(bool newRequestPTC);

    bool requestSound() const;
    void setRequestSound(bool new_);

    // status
    bool isCrashed() const;
    void setIsCrashed(bool newIsCrashed);

    bool isDestoried() const;
    void setIsDestoried(bool newIsDestoried);

    bool isCompleted() const;
    void setIsCompleted(bool newIsCompleted);

    PhiViewer *phiViewer() const;
    void setPhiViewer(PhiViewer *newPhiViewer);

    PhiJudgeLine *judgeLine() const;
    void setJudgeLine(PhiJudgeLine *newJudgeLine);

public slots:
    void checkHighLight();
    void checkTypeIndex();

    void updateRFloorPostion();
    void initRFloorPostion();
    void initSpeed();

public:
    virtual void checkTime();
    virtual void crash();

    int endTime() const;
    void setEndTime(int newEndTime);

private:
    // basic info
    QString m_type       = "tap";
    int     m_typeIndex  = 0;
    qreal   m_posX       = 0;
    qreal   m_rFloorPos  = 1;
    qreal   m_speed      = 0.3;
    qreal   m_basicSpeed = 0.3;
    qreal   m_time       = INT_MAX;
    QString m_position   = "above";

    int m_endTime        = INT_MAX;

    // others
    PhiViewer*    m_phiViewer = nullptr;
    PhiJudgeLine* m_judgeLine = nullptr;

    // status
    bool m_highLight   = false;
    bool m_isCrashed   = false;
    bool m_isDestoried = false;
    bool m_isCompleted = false;

    // request status
    bool m_requestPTC   = false;
    bool m_requestSound = false;


signals:
    void typeChanged();
    void typeIndexChanged();
    void posXChanged();
    void speedChanged();
    void basicSpeedChanged();
    void timeChanged();
    void positionChanged();

    // status
    void highLightChanged();
    void requestPTCChanged();
    void crashed();

    // request status
    void requestSoundChanged();
    void requestedSound(int);

    void phiViewerChanged();
    void judgeLineChanged();
};

#endif // PHIABSTRACTNOTE_H
