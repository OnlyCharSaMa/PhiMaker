#include "../functions/Math2d.h"
#include "phievent.h"
#include "phijudgeline.h"
#include "phiabstractnote.h"
#include "../Widgets/phiviewer.h"

#ifdef QT_DEBUG
#include <QMessageBox>
#include <QDebug>
#endif

PhiJudgeLine::PhiJudgeLine(PhiViewer *phiViewer,
                           QObject *parent)
    : QObject{parent}
{
#ifdef QT_DEBUG
    qDebug() << "JudgeLine的初始化开始";
#endif

#ifdef QT_DEBUG
    if(phiViewer == nullptr)
    {
        QMessageBox::warning(nullptr, "drawNote函数出现bug", "判定线是空指针, 请联系开发者");
    }
#endif

    setPhiViewer(phiViewer);

#ifdef QT_DEBUG
    qDebug() << "为PhiViewer赋值成功";
#endif

    connect(m_phiViewer, &PhiViewer::currentTimeChanged,
            [=](){setCurrentTime(m_phiViewer->currentTime());} );
    // 因为当phiViewer被销毁时会自动释放所有判定线所以这里就忽略warning

#ifdef QT_DEBUG
    qDebug() << "JudgeLine的currentTimeChanged信号与m_currentTime的赋值绑定完成";
#endif

    m_verAnm.setTargetObject(this);
    m_horAnm.setTargetObject(this);
    m_rotateAnm.setTargetObject(this);
    m_disappearAnm.setTargetObject(this);
    m_speedAnm.setTargetObject(this);

    m_verAnm.setPropertyName("ver");
    m_horAnm.setPropertyName("hor");
    m_rotateAnm.setPropertyName("rotate");
    m_disappearAnm.setPropertyName("alpha");
    m_speedAnm.setPropertyName("speed");

#ifdef QT_DEBUG
    qDebug() << "给JudgeLine的动画设置target和property";
#endif

#ifdef QT_DEBUG
    qDebug() << "JudgeLine的初始化完成";
#endif
}



qreal PhiJudgeLine::rotate() const
{
    return m_rotate;
}

void PhiJudgeLine::setRotate(qreal newRotate)
{
    if (qFuzzyCompare(m_rotate, newRotate))
        return;
    m_rotate = newRotate;
    emit rotateChanged();

    // 将arc属性和setrotate函数绑定
    setArc(angleToArc(m_rotate));
}

qreal PhiJudgeLine::arc() const
{
    return m_arc;
}

void PhiJudgeLine::setArc(qreal newArc)
{
    m_arc = newArc;
}

const QVector<PhiAbstractNote *> &PhiJudgeLine::noteList() const
{
    return m_noteList;
}

void PhiJudgeLine::setNoteList(const QVector<PhiAbstractNote *> &newNoteList)
{
    m_noteList = newNoteList;
}

qreal PhiJudgeLine::speed() const
{
    return m_speed;
}

void PhiJudgeLine::setSpeed(qreal newSpeed)
{
    if (qFuzzyCompare(m_speed, newSpeed))
        return;
    m_speed = newSpeed;
    emit speedChanged();
}



void PhiJudgeLine::initAllEvents()
{
    initVerMoveAnm();
    initHorMoveAnm();
    initRotateAnm();
    initDisappearAnm();
    initSpeedAnm();
}

void PhiJudgeLine::startAllEvents()
{
    if(m_verMoveEvents.length() > 0)
    {m_verAnm.start();}
    if(m_horMoveEvents.length() > 0)
    {m_horAnm.start();}
    if(m_rotateEvents.length() > 0)
    {m_rotateAnm.start();}
    if(m_disappearEvents.length() > 0)
    {m_disappearAnm.start();}
    if(m_speedEvents.length() > 0)
    {m_speedAnm.start();}
}

void PhiJudgeLine::resumeAllEvents()
{
    m_verAnm.resume();
    m_horAnm.resume();
    m_rotateAnm.resume();
    m_disappearAnm.resume();
    m_speedAnm.resume();
}

void PhiJudgeLine::restartAllEvents()
{
    m_verEventIndex         = 0;
    m_horEventIndex         = 0;
    m_rotateEventIndex      = 0;
    m_disappearEventIndex   = 0;

    initAllEvents();// needs to init To load original events

    startAllEvents();
}

void PhiJudgeLine::pauseAllEvents()
{
    m_verAnm.pause();
    m_horAnm.pause();
    m_rotateAnm.pause();
    m_disappearAnm.pause();
    m_speedAnm.pause();
}

void PhiJudgeLine::initVerMoveAnm()
{
    if(m_verMoveEvents.length() > 0)
    {
        PhiEvent* verEvent = m_verMoveEvents[m_verEventIndex];
        m_verAnm.setDuration(verEvent->endTime() - verEvent->startTime());
        m_verAnm.setStartValue(verEvent->start());
        m_verAnm.setEndValue(verEvent->end());
        m_verAnm.setEasingCurve(verEvent->getCurve());
    }
}

void PhiJudgeLine::initHorMoveAnm()
{
    if(m_horMoveEvents.length() > 0)
    {
        PhiEvent* horEvent = m_horMoveEvents[m_horEventIndex];
        m_horAnm.setDuration(horEvent->endTime() - horEvent->startTime());
        m_horAnm.setStartValue(horEvent->start());
        m_horAnm.setEndValue(horEvent->end());
        m_horAnm.setEasingCurve(horEvent->getCurve());
    }
}

void PhiJudgeLine::initRotateAnm()
{
    if(m_rotateEvents.length() > 0)
    {
        PhiEvent* rotateEvent = m_rotateEvents[m_rotateEventIndex];
        m_rotateAnm.setDuration(rotateEvent->endTime() - rotateEvent->startTime());
        m_rotateAnm.setStartValue(rotateEvent->start());
        m_rotateAnm.setEndValue(rotateEvent->end());
        m_rotateAnm.setEasingCurve(rotateEvent->getCurve());
    }
}

void PhiJudgeLine::initDisappearAnm()
{
    if(m_disappearEvents.length() > 0)
    {
        PhiEvent* disappearEvent = m_disappearEvents[m_disappearEventIndex];
        m_disappearAnm.setDuration(disappearEvent->endTime() - disappearEvent->startTime());
        m_disappearAnm.setStartValue(disappearEvent->start());
        m_disappearAnm.setEndValue(disappearEvent->end());
        m_disappearAnm.setEasingCurve(disappearEvent->getCurve());
    }
}

void PhiJudgeLine::initSpeedAnm()
{
    if(m_speedEvents.length() > 0)
    {
        PhiEvent* speedEvent = m_speedEvents[m_speedEventIndex];
        m_speedAnm.setDuration(speedEvent->endTime() - speedEvent->startTime());
        m_speedAnm.setStartValue(speedEvent->start());
        m_speedAnm.setEndValue(speedEvent->end());
        m_speedAnm.setEasingCurve(speedEvent->getCurve());
    }
}

qreal PhiJudgeLine::alpha() const
{
    return m_alpha;
}

void PhiJudgeLine::setAlpha(qreal newAlpha)
{
    if (qFuzzyCompare(m_alpha, newAlpha))
        return;
    m_alpha = newAlpha;
    emit alphaChanged();
}

qreal PhiJudgeLine::hor() const
{
    return m_hor;
}

void PhiJudgeLine::setHor(qreal newHor)
{
    if (qFuzzyCompare(m_hor, newHor))
        return;
    m_hor = newHor;
    emit horChanged();
}

qreal PhiJudgeLine::ver() const
{
    return m_ver;
}

void PhiJudgeLine::setVer(qreal newVer)
{
    if (qFuzzyCompare(m_ver, newVer))
        return;
    m_ver = newVer;
    emit verChanged();
}

int PhiJudgeLine::currentTime() const
{
    return m_currentTime;
}

void PhiJudgeLine::setCurrentTime(int newCurrentTime)
{
    if (m_currentTime == newCurrentTime)
        return;
    m_currentTime = newCurrentTime;
    emit currentTimeChanged();
}

PhiViewer *PhiJudgeLine::phiViewer() const
{
    return m_phiViewer;
}

void PhiJudgeLine::setPhiViewer(PhiViewer *newPhiViewer)
{
    if (m_phiViewer == newPhiViewer)
        return;
    m_phiViewer = newPhiViewer;
    emit phiViewerChanged();
}

void PhiJudgeLine::addNote(PhiAbstractNote *note)
{
    m_noteList.push_back(note);
}

void PhiJudgeLine::removeNote(int index)
{
    m_noteList.remove(index);
}

void PhiJudgeLine::addNote_autoSort(PhiAbstractNote *note)
{
    // 这里已经默认了noteList是按endTime升序来排的

    // 三种特殊情况qwq
    if(m_noteList.length() == 0)
    {m_noteList.push_back(note);
     return;
    }
    else if(note->endTime() < m_noteList.first()->endTime())
    {m_noteList.push_front(note);
     return;
    }
    else if(note->endTime() > m_noteList.last()->endTime())
    {m_noteList.push_back(note);
     return;
    }


    int l = 0;
    int r = m_noteList.length() - 1;
    int mid;
    int correctPos;

    while(r >= l)
    {
        mid = (l + r) / 2;
        if(note->endTime() > m_noteList[mid]->endTime())
        {
            l = mid + 1;
        }
        else if(note->endTime() < m_noteList[mid]->endTime())
        {
            r = mid - 1;
        }
        else
        {
            correctPos = mid;
            break;
        }
    }
    correctPos = r;

    m_noteList.insert(correctPos, note);
    /* Old Code
        if(note->endTime() > m_noteList[index]->endTime())
        {
            if(note->endTime() <= m_noteList[index+1]->endTime())
            {
                m_noteList.insert(index+1, note);
                break;
            }
            else
            {
                index = (m_noteList.length() - 1 + index) / 2;
            }
        }
        else if(note->endTime() < m_noteList[index]->endTime()){
            if (note->endTime() >= m_noteList[index-1]->endTime())
            {
                m_noteList.insert(index, note);
                break;
            }
            else {
                index = index / 2;
            }
        }
        else {
            m_noteList.insert(index+1, note);
            break;
        }
    */
}

void PhiJudgeLine::addEvent_autoSort(EventType type, PhiEvent *event)
{
    // 这里已经默认了eventList是按startTime升序来排的
    // 因为反正event都不能相互重合所以写复杂的检测没啥用，再加上我们可以直接写个ui帮助首尾相连（（
    QVector<PhiEvent*>* v;
    switch(type)
    {
    case HorMove:
        v = &m_horMoveEvents;
        break;

    case VerMove:
        v = &m_verMoveEvents;
        break;

    case Rotate:
        v = &m_rotateEvents;
        break;

    case Disappear:
        v = &m_disappearEvents;
        break;

    case Speed:
        v = &m_speedEvents;
        break;
    }



    if(v->length() == 0)
    {v->push_back(event);
     return;
    }
    else if(event->startTime() < v->first()->startTime())
    {v->push_front(event);
     return;
    }
    else if(event->startTime() > v->last()->startTime())
    {v->push_back(event);
     return;
    }

    int l = 0;
    int r = v->length() - 1;
    int mid;
    int correctPos;
    while(r >= l)
    {
        mid = (l + r) / 2;
        if(event->startTime() > v->at(mid)->startTime())
        {
            l = mid + 1;
        }
        else if(event->startTime() < v->at(mid)->startTime())
        {
            r = mid - 1;
        }
        else
        {
            correctPos = mid;
        }
    }

    correctPos = r;
    v->insert(correctPos, event);

    /*  Old Code
        if(event->startTime() > v->at(index)->startTime())
        {
            if(event->startTime() <= v->at(index+1)->startTime())
            {
                v->insert(index+1, event);
                break;
            }
            else
            {
                index = (v->length() - 1 + index) / 2;
            }
        }
        else if(event->startTime() < v->at(index)->startTime()){
            if(event->startTime() >= v->at(index-1)->startTime())
            {
                v->insert(index, event);
                break;
            }
            else {
                index = index / 2;
            }
        }
        else {
            v->insert(index+1, event);
            break;
        }
    */
}


