#include "phiviewer.h"
#include "../PhigrosObj/phiabstractnote.h"
#include "../PhigrosObj/phinote.h"
#include "../PhigrosObj/phihold.h"
#include "../PhigrosObj/phijudgeline.h"
#include "../PhigrosObj/phihitptc.h"
#include "../PhigrosObj/phihitptcdata.h"
#include <QOpenGLWidget>
#include <QFrame>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QVector>

#ifdef QT_DEBUG
#include <QMessageBox>
#include <QDebug>
#endif

PhiViewer::PhiViewer(QWidget *parent)
    : QOpenGLWidget{parent}
{
#ifdef QT_DEBUG
    qDebug() << "PhiViewer 开始执行初始化函数(init)";
#endif

    // 设置固定的宽高
    setFixedHeight(800);
    setFixedWidth(1300);

    // 加载打击音效贴图文件
    {
    QString tempStr;
    QString realFile;
    for(int i = 0; i < 30; i++)
    {
        tempStr = QString::number(i);
        realFile = ":/res/phi/perfect_particle/HitParticle (" + tempStr + ")_perfect.png";
        m_hitPTCImg.push_back(QImage(realFile));
    }
    }

    // 设置调色板和背景
    QPalette pal;
    pal.setColor(QPalette::Background, QColor(255, 255, 255, 133));
    setPalette(pal);
    setAutoFillBackground(true);

    // 设置自动刷新
    QTimer* updateTimer = new QTimer(this);
    updateTimer->setInterval(1000 / m_fps);
    updateTimer->start();
    connect(updateTimer, SIGNAL(timeout()),
            this,        SLOT(update()));

    // 目前的时间
    m_timeAnm.setTargetObject(this);
    m_timeAnm.setPropertyName("currentTime");
    m_timeAnm.setDuration(INT_MAX);
    m_timeAnm.setStartValue(0);
    m_timeAnm.setEndValue(INT_MAX);

    // 线程管理
    m_audioThread  = new QThread;
    m_player =       new PhiSoundPlayer;
    m_player->moveToThread(m_audioThread);
    m_audioThread->start(QThread::NormalPriority);




#ifdef QT_DEBUG
    qDebug() << "PhiViewer 初始化函数(init)完成";
#endif
}

void PhiViewer::paintEvent(QPaintEvent *e)
{
    painter.begin(this);

    drawBackground();
    drawMask();
    drawJudgeLines();
    drawNotes();
    drawHitPTCs();

    painter.end();
}

void PhiViewer::resizeEvent(QResizeEvent *e)
{
    // 因为在类初始化时没有size所以在这里处理
    m_backgroundImg = m_original_backgroundImg.scaled(e->size(), Qt::KeepAspectRatioByExpanding);
    update();

#ifdef QT_DEBUG
    qDebug() << "处理完resized信号了";
#endif
}

void PhiViewer::drawBackground()
{
    painter.drawImage(
                0,
                (this->height() - m_backgroundImg.height()) / 2,
                m_backgroundImg);
}

void PhiViewer::drawMask()
{
    painter.fillRect(this->rect(), m_maskBrush);
}

inline void PhiViewer::drawJudgeLines()
{
    int jlWidth = this->height() * 0.005;
    painter.setPen(QPen(QBrush(m_perfectColor), jlWidth));

    for(auto jl : m_judgeLineList)
    {
        drawJudgeLine(jl);
    }
}

inline void PhiViewer::drawNotes()
{
    for(int i = 0; i < m_judgeLineList.length(); i++)
    {
        PhiJudgeLine* jl = m_judgeLineList[i];
        for(int j = m_jumpNoteCount; j < jl->noteList().length(); j++)
        {

            PhiAbstractNote* note = jl->noteList()[j];
            note->updateRFloorPostion();
            note->checkTime();

            if(note->RequestPTC() == true)
            {
                createHitPTC(jl->hor()    * this->width(),
                             jl->ver()    * this->height(),
                             jl->rotate(),
                             note->posX() * this->width()
                             );
                note->setRequestPTC(false); // after meet its need(create hitParticle) then set it to false
            }


            if(note->isCrashed() == true)
            {
                m_jumpNoteCount++;
                continue;
            }

            else if(note->rFloorPos() > 2){break;}
            else
            {
                drawNote(note);
            }
        }
    }


}

inline void PhiViewer::drawHitPTCs()
{


    for(PhiHitPTCData* ptc : m_hitPTCDatas)
    {
        painter.translate(ptc->x, ptc->y);
        painter.rotate(ptc->rotate);
        painter.translate(ptc->xOffset, 0);
        painter.rotate(-ptc->rotate);
        drawFixedImage(
                m_hitPTCImg[ptc->imgIndex],
                0,
                0,
                m_hitPTCWidth,
                m_hitPTCWidth
                );
        painter.rotate(ptc->rotate);
        painter.translate(-ptc->xOffset, 0);
        painter.rotate(-ptc->rotate);
        painter.translate(-ptc->x, -ptc->y);
        delete ptc;
    }
    m_hitPTCDatas = {};


}

inline void PhiViewer::drawJudgeLine(PhiJudgeLine* jl)
{
    drawLongLine(
                jl->hor() * this->width(),
                jl->ver() * this->height(),
                jl->rotate()
                );
}

inline void PhiViewer::drawNote(PhiAbstractNote *note)
{
    PhiJudgeLine* jl = note->judgeLine();

#ifdef QT_DEBUG
    if(jl == nullptr){QMessageBox::warning(this, "drawNote函数出现bug", "判定线是空指针, 请联系开发者");}
#endif

    painter.translate(jl->hor() * this->width(), jl->ver() * this->height());
    painter.rotate(jl->rotate());

    if(note->type() == "hold"){drawHold(static_cast<PhiHold*>(note));}
    else{drawTap(static_cast<PhiNote*>(note));}

    painter.rotate(-jl->rotate());
    painter.translate(-jl->hor() * this->width(), -jl->ver() * this->height());

}

void PhiViewer::drawTap(PhiNote *note)
{
     note->checkTime();

    if(note->position() == "below")
    {
        drawFixedImage(
                    m_noteImgList[note->typeIndex()],
                    note->posX()      * this->width(),
                    note->rFloorPos() * this->height(), // 具体见 项目根目录/doc/draw-Note-position.txt
                    m_noteWs[note->typeIndex()],
                    m_noteHs[note->typeIndex()]
                );
    }
    else
    {
        drawFixedImage(
                    m_noteImgList[note->typeIndex()],
                    note->posX()      * this->width(),
                    -note->rFloorPos() * this->height(), // 具体见 项目根目录/doc/draw-Note-position.txt
                    m_noteWs[note->typeIndex()],
                    m_noteHs[note->typeIndex()]
                );
    }

}

inline void PhiViewer::drawHold(PhiHold *note)
{

    if(note->position() == "below")
    {
        painter.scale(1 ,-1);
    }

    // note size
    // 才发现tnnd有这么多弊端, 历史遗留问题+1
    // 因为qml的数据绑定机制，我当时就偷了下懒，也没想到放C++要像这样庞大

    qreal rFloorPosLength = note->holdTime() * note->speed() / 1000;
    qreal rEndFloorPos    = note->rFloorPos() + rFloorPosLength;

    int centerX         = note->posX() * this->width();        // 这里的绘图逻辑与qml不同，但是其实只是计算note的位置不同而已
    int headY           = -note->rFloorPos() * this->height(); // 现在已经搞清楚了基本原理和 根目录/doc/draw-Note-position.txt 一致
    int m_holdHeadRH = m_noteHs[note->typeIndex()];            // 因为历史原因 两个负号（与上面的 scale）抵消了，我也不想清理这堆古老的代码，等以后再说吧
    int m_holdHeadRW = m_noteWs[note->typeIndex() - 1];        // 毕竟绘图函数一旦成型也没啥需要改的了，这里顶多只是会难以理解而已，影响不大
    QPoint&& headLeftTop = centerToLeftTop(centerX, headY, m_holdHeadRW, m_holdHeadRW);


    int endY             = -rEndFloorPos * this->height();
    QPoint&& endLeftTop  = centerToLeftTop(centerX, endY, m_holdEndW, m_holdEndH);


    int m_holdBodyRH = -endLeftTop.y() - m_holdEndH  + headLeftTop.y();
    QPoint bodyLeftTop(endLeftTop.x(), endLeftTop.y() + m_holdEndH);

    int headClipHeight = (headLeftTop.y() + m_holdHeadRH);
    int bodyClipHeight = headClipHeight - m_holdHeadRH;
    int endClipHeight  = bodyClipHeight - m_holdBodyRH;



    //note.
    if(headClipHeight > 0)
    {
        if(headClipHeight < m_holdHeadRH)
        {
            painter.drawImage(
                QRect(
                    headLeftTop.x(),
                    headLeftTop.y(),
                    m_holdHeadRW,
                    m_holdHeadRH - headClipHeight
                ),

                m_noteImgList[note->typeIndex()],

                QRect(
                    0,
                    0,
                    m_o_noteWs[note->typeIndex()],
                    (m_holdHeadRH - headClipHeight) / m_noteZoom

                )
            );
        }
    }
    else
    {
        painter.drawImage(
            QRect(
                headLeftTop.x(),
                headLeftTop.y(),
                m_holdHeadRW,
                m_holdHeadRH
                ),
            m_noteImgList[note->typeIndex()]
        );
    }


    // draw Body
    if(bodyClipHeight > 0)
    {
        if(bodyClipHeight < m_holdBodyRH)
        {
            painter.drawImage(
                   QRect(
                       bodyLeftTop.x(),
                       bodyLeftTop.y(),
                       m_holdBodyW,
                       m_holdBodyRH - bodyClipHeight
                       ),

                   m_img_hold,

                   QRect(
                       0,
                       0,
                       m_o_holdBodyW,
                       m_o_holdBodyH
                    )
            );
        }

    }
    else
    {
        painter.drawImage(
             QRect(
                 bodyLeftTop.x(),
                 bodyLeftTop.y(),
                 m_holdBodyW,
                 m_holdBodyRH),
             m_img_hold
        );
    }


    // draw End
    if(endClipHeight > 0)
    {
        if(endClipHeight < m_holdEndH)
        {
            painter.drawImage(
                 QRect(
                     endLeftTop.x(),
                     endLeftTop.y(),
                     m_holdEndW,
                     m_holdEndH - endClipHeight
                 ),

                 m_img_holdEnd,

                 QRect(
                     0,
                     0,
                     m_o_holdEndW,
                     (m_holdEndH - endClipHeight) / m_noteZoom
                 )
            );
        }
    }
    else
    {
        painter.drawImage(
                    QRect(
                        endLeftTop.x(),
                        endLeftTop.y(),
                        m_holdEndW,
                        m_holdEndH
                    ),
                    m_img_holdEnd
        );
    }



    if(note->position() == "below")
    {
        painter.scale(1 ,-1);
    }
}



void PhiViewer::drawLongLine(int x, int y, qreal rotate)
{
    painter.translate(x, y);
    painter.rotate(rotate);
    painter.drawLine(-this->width()*10, 0, this->width()*10, 0);
    painter.rotate(-rotate);
    painter.translate(-x, -y);
}

void PhiViewer::drawFixedImage(QImage img, int center_x, int center_y, int width, int height)
{
    painter.drawImage(
                QRect(
                    center_x - width / 2,
                    center_y - height / 2,
                    width,
                    height
                    ),
                img
                );
}



PhiSoundPlayer *PhiViewer::player() const
{
    return m_player;
}

void PhiViewer::setPlayer(PhiSoundPlayer *newPlayer)
{
    m_player = newPlayer;
}

int PhiViewer::currentTime() const
{
    return m_currentTime;
}

void PhiViewer::setCurrentTime(int newCurrentTime)
{
    if (m_currentTime == newCurrentTime)
        return;
    m_currentTime = newCurrentTime;
    emit currentTimeChanged();


}

void PhiViewer::pushJudgeLine(PhiJudgeLine * jl)
{
    m_judgeLineList.push_back(jl);
}


void PhiViewer::setSize(const QSize& size)
{
    this->resize(size);
    this->update();

#ifdef QT_DEBUG
    qDebug() << "PhiViewer重设了大小."
             << " 宽为: " << size.width()
             << " 高为: " << size.height();
#endif
}

void PhiViewer::initChart()
{
    for(auto jl : m_judgeLineList)
    {
        jl->initAllEvents();
    }
}

void PhiViewer::startChart()
{
    emit chartStarted();
    m_timeAnm.start();
    for(auto jl : m_judgeLineList)
    {
        jl->startAllEvents();
    }
    m_mediaPlayer.play();
}


void PhiViewer::resumeChart()
{
    emit chartStarted();
    m_mediaPlayer.play();
    m_timeAnm.resume();
    for(auto jl : m_judgeLineList)
    {
        jl->resumeAllEvents();
    }
}

void PhiViewer::restartChart()
{
    emit chartStarted();
    m_timeAnm.stop();
    m_timeAnm.setCurrentTime(0);
    m_timeAnm.start();
    m_mediaPlayer.setPosition(0);
    m_mediaPlayer.play();
    for(auto jl : m_judgeLineList)
    {
        jl->restartAllEvents();
    }
}

void PhiViewer::pauseChart()
{
    emit chartPaused();
    m_timeAnm.pause();
    m_mediaPlayer.pause();
    for(auto jl : m_judgeLineList)
    {
        jl->pauseAllEvents();
    }
}

void PhiViewer::createHitPTC(int x, int y, qreal rotate, int xOffset,int imgIndex)
{
    PhiHitPTC* ptc = new PhiHitPTC(x, y, rotate, xOffset, imgIndex);
    connect(ptc,  SIGNAL(requestHitPTC(int,int,qreal,int,int)),
            this, SLOT(createHitPTCData(int,int,qreal,int,int)));
}

void PhiViewer::createHitPTCData(int x, int y, qreal rotate, int xOffset, int imgIndex)
{
    PhiHitPTCData* data = new PhiHitPTCData();

    data->x        = x;
    data->y        = y;
    data->imgIndex = imgIndex;
    data->xOffset  = xOffset;
    data->rotate   = rotate;

    m_hitPTCDatas.push_back(data);
}

void PhiViewer::updateAllPaintSize()
{
    updateHitPTCSize();

#ifdef QT_DEBUG
    qDebug() << "更新了所有绘画对象的大小";
#endif
}

void PhiViewer::updateHitPTCSize()
{
    m_hitPTCWidth = m_o_hitPTCWidth * m_noteZoom;

#ifdef QT_DEBUG
    qDebug() << "更新了所有打击特效的大小";
#endif
}

void PhiViewer::initAllNoteSize()
{
    for(short i = 0; i < 8; i++)
    {
        m_noteWs[i] = m_o_noteWs[i] * m_noteZoom;
        m_noteHs[i] = m_o_noteHs[i] * m_noteZoom;
    }
}

int PhiViewer::o_hitPTCWidth() const
{
    return m_o_hitPTCWidth;
}

void PhiViewer::setO_hitPTCWidth(int newO_hitPTCWidth)
{
    if (m_o_hitPTCWidth == newO_hitPTCWidth)
        return;
    m_o_hitPTCWidth = newO_hitPTCWidth;
    emit o_hitPTCWidthChanged();
}

qreal PhiViewer::noteZoom() const
{
    return m_noteZoom;
}

void PhiViewer::setNoteZoom(qreal newNoteZoom)
{
    if (qFuzzyCompare(m_noteZoom, newNoteZoom))
        return;
    m_noteZoom = newNoteZoom;
    emit noteZoomChanged();
}

int PhiViewer::fps() const
{
    return m_fps;
}

void PhiViewer::setFps(int newFps)
{
    if (m_fps == newFps)
        return;
    m_fps = newFps;
    emit fpsChanged();
}




