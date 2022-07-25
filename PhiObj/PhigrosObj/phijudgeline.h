#ifndef PHIJUDGELINE_H
#define PHIJUDGELINE_H

#include "../functions/Math2d.h"
#include "../classesDeclaration.h"
#include <QVector>
#include <QObject>
#include <QPropertyAnimation>

class PhiJudgeLine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal ver READ ver WRITE setVer NOTIFY verChanged)
    Q_PROPERTY(qreal hor READ hor WRITE setHor NOTIFY horChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qreal rotate READ rotate WRITE setRotate NOTIFY rotateChanged)
    Q_PROPERTY(qreal alpha READ alpha WRITE setAlpha NOTIFY alphaChanged)
    Q_PROPERTY(int currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)

    enum EventType {HorMove, VerMove, Rotate, Disappear, Speed};

public:
    explicit PhiJudgeLine(
            PhiViewer* phiViewer,
            QObject *parent = nullptr);

    qreal ver() const;
    void setVer(qreal newVer);

    qreal hor() const;
    void setHor(qreal newHor);

    qreal rotate() const;
    void setRotate(qreal newRotate);

    qreal arc() const;
    void setArc(qreal newArc);

    const QVector<PhiAbstractNote *> &noteList() const;
    void setNoteList(const QVector<PhiAbstractNote *> &newNoteList);

    qreal speed() const;
    void setSpeed(qreal newSpeed);

    PhiViewer *phiViewer() const;
    void setPhiViewer(PhiViewer *newPhiViewer);

    int currentTime() const;
    void setCurrentTime(int newCurrentTime);

    qreal alpha() const;
    void setAlpha(qreal newAlpha);


public:
    // vector 相关操作
    void addNote(PhiAbstractNote* note);
    void removeNote(int index);

    void addNote_autoSort(PhiAbstractNote* note);
    void addEvent_autoSort(EventType type, PhiEvent* event);

public slots:
    void initAllEvents();
    void startAllEvents();
    void resumeAllEvents();
    void restartAllEvents();
    void pauseAllEvents();

    void initVerMoveAnm();
    void initHorMoveAnm();
    void initRotateAnm();
    void initDisappearAnm();
    void initSpeedAnm();

private:
    QVector<PhiAbstractNote*> m_noteList;

    // basic paint infomation
    qreal m_ver     = 0.5;
    qreal m_hor     = 0.5;
    qreal m_rotate  = 0;
    qreal m_arc     = 0;
    qreal m_alpha   = 1;


    // performance
    qreal m_color_red     = 1;
    qreal m_color_green   = 0.843;
    qreal m_color_blue    = 0;
    qreal m_speed         = 0;

    // event List
    QVector<PhiEvent*> m_verMoveEvents  ;
    QVector<PhiEvent*> m_horMoveEvents  ;
    QVector<PhiEvent*> m_rotateEvents   ;
    QVector<PhiEvent*> m_disappearEvents;
    QVector<PhiEvent*> m_speedEvents    ;

    int m_verEventIndex       = 0;
    int m_horEventIndex       = 0;
    int m_rotateEventIndex    = 0;
    int m_disappearEventIndex = 0;
    int m_speedEventIndex     = 0;

    // Anm
    QPropertyAnimation m_verAnm;
    QPropertyAnimation m_horAnm;
    QPropertyAnimation m_rotateAnm;
    QPropertyAnimation m_disappearAnm;
    QPropertyAnimation m_speedAnm;

    // other
    int m_jlIndex;
    int m_currentTime;
    PhiViewer* m_phiViewer;



signals:
    void rotateChanged();
    void speedChanged();
    void phiViewerChanged();
    void currentTimeChanged();
    void verChanged();
    void horChanged();
    void alphaChanged();
};

#endif // PHIJUDGELINE_H
