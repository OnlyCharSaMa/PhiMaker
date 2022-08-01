#ifndef PHIVIEWER_H
#define PHIVIEWER_H

#include "../classesDeclaration.h"
#include "../../phisoundplayer.h"
#include <QPainter>
#include <QVector>
#include <QImage>
#include <QLabel>
#include <QThread>
#include <QOpenGLWidget>
#include <QMediaPlayer>
#include <QPropertyAnimation>


class PhiViewer : public QOpenGLWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(int fps READ fps WRITE setFps NOTIFY fpsChanged)
    Q_PROPERTY(qreal noteZoom READ noteZoom WRITE setNoteZoom NOTIFY noteZoomChanged)
    Q_PROPERTY(int o_hitPTCWidth READ o_hitPTCWidth WRITE setO_hitPTCWidth NOTIFY o_hitPTCWidthChanged)


public:
    explicit PhiViewer(QWidget *parent = nullptr);

    // 事件
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

    // phi的绘图函数
    inline void drawBackground();
    inline void drawMask();
    inline void drawJudgeLines();
    inline void drawNotes();
    inline void drawHitPTCs();
    inline void drawJudgeLine(PhiJudgeLine* jl);
    inline void drawNote(PhiAbstractNote* note);
    void drawTap(PhiNote* note);
    void drawHold(PhiHold* note);

    // draw API
    inline void drawLongLine(int x, int y, qreal rotate);
    inline void drawFixedImage(QImage img, int x, int y, int width, int height);
    inline void drawFixedImageEx(QImage img, int x, int y, int width, int height, int zoom = 1);


public:
    // getter 与 setter
    PhiSoundPlayer *player() const;
    void setPlayer(PhiSoundPlayer *newPlayer);

    int currentTime() const;
    void setCurrentTime(int newCurrentTime);

    // 自己的接口
    void pushJudgeLine(PhiJudgeLine*);

    int fps() const;
    void setFps(int newFps);

    qreal noteZoom() const;
    void setNoteZoom(qreal newNoteZoom);

    int o_hitPTCWidth() const;
    void setO_hitPTCWidth(int newO_hitPTCWidth);

public slots:
    // QT object (窗口)相关的槽函数
    void setSize(const QSize&);

    // chart相关的
    void initChart();
    void startChart();
    void resumeChart();
    void restartChart();
    void pauseChart();

    //// 画面相关
    // 打击特效相关
    void createHitPTC(int x, int y, qreal rotate, int xOffset, int imgIndex = 0);
    void createHitPTCData(int x, int y, qreal rotate, int xOffset,int imgIndex);
    // 绘图相关
    void updateAllPaintSize();
    void updateHitPTCSize();
    // 贴图
    void initAllNoteSize();



private:
    // 线程管理
    QThread* m_audioThread;

    // paint performance
    QColor m_perfectColor = QColor(255, 192, 0);
    QColor m_maskColor    = QColor(0, 0, 0, 133);
    QBrush m_maskBrush    = QBrush(m_maskColor);
    QVector<PhiHitPTCData*> m_hitPTCDatas;

    // 画面相关
    int     m_fps           = 60;
    qreal   m_noteZoom      = 0.15;
    int     m_o_hitPTCWidth = 1200;
    int     m_hitPTCWidth   = m_o_hitPTCWidth * m_noteZoom;

    // 绘制相关
    int m_jumpNoteCount = 0; // 设置一个跳过已经无需绘制的Note数量

    // chart
    QVector<PhiJudgeLine*> m_judgeLineList ;

    // basic Infomation
    QString m_formatVersion   = "PhiMaker Chart Standard 1.0";
    QString m_musician        = "null musician";
    QString m_charter         = "null charter";
    QString m_illustrator     = "null illustrator";
    QString m_chartLevel      = "FM Lv.?";
    QString m_musicName       = "null music name";

    // invisible info
    qreal bpm;

    // others
    int  m_currentTime                  = 0;
    QPainter            painter         = QPainter(this);
    QMediaPlayer        m_mediaPlayer   = QMediaPlayer(this);
    PhiSoundPlayer*     m_player; // play sound
    QPropertyAnimation  m_timeAnm;// cotrol m_currentTime

    // 贴图
    QImage m_original_backgroundImg = QImage(":/res/Phigros_Icon_New.png");
    QImage m_backgroundImg          = m_original_backgroundImg;

    QVector<QImage> m_noteImgList = {
        QImage(":/res/phi/notes/Tap.png"),
        QImage(":/res/phi/notes/Drag.png"),
        QImage(":/res/phi/notes/Flick.png"),
        QImage(":/res/phi/notes/Hold_Head.png"),
        QImage(":/res/phi/notes/TapHL.png"),
        QImage(":/res/phi/notes/FlickHL.png"),
        QImage(":/res/phi/notes/DragHL.png"),
        QImage(":/res/phi/notes/Hold_HeadHL.png")
    };

    QImage m_img_hold    = QImage(":/res/phi/notes/Hold.png");
    QImage m_img_holdEnd = QImage(":/res/phi/notes/Hold_End.png");


    QVector<QImage> m_hitPTCImg;

    // 贴图大小
    QVector<int> m_o_noteWs = {
        989,//tap
        989,//drag
        989,//flick
        989,//hold_head
        1089,//tap hl
        1089,//drag hl
        1089,//flick hl
        1058//hold_head hl
    };

    QVector<int> m_o_noteHs = {
        100,//tap
        60,//drag
        200,//flick
        50,//hold_head
        200,//tap hl
        160,//drag hl
        300,//flick hl
        97//hold_head hl
    };

    QVector<int> m_noteWs = {
        int(m_o_noteWs[0] * m_noteZoom),//tap
        int(m_o_noteWs[1] * m_noteZoom),//drag
        int(m_o_noteWs[2] * m_noteZoom),//flick
        int(m_o_noteWs[3] * m_noteZoom),//hold_head
        int(m_o_noteWs[4] * m_noteZoom),//tap hl
        int(m_o_noteWs[5] * m_noteZoom),//drag hl
        int(m_o_noteWs[6] * m_noteZoom),//flick hl
        int(m_o_noteWs[7] * m_noteZoom)//hold_head hl
    };

    QVector<int> m_noteHs = {
        int(m_o_noteHs[0] * m_noteZoom),//tap
        int(m_o_noteHs[1] * m_noteZoom),//drag
        int(m_o_noteHs[2] * m_noteZoom),//flick
        int(m_o_noteHs[3] * m_noteZoom),//hold_head
        int(m_o_noteHs[4] * m_noteZoom),//tap hl
        int(m_o_noteHs[5] * m_noteZoom),//drag hl
        int(m_o_noteHs[6] * m_noteZoom),//flick hl
        int(m_o_noteHs[7] * m_noteZoom)//hold_head hl
    };


    int m_o_holdBodyW = 989 ;
    int m_o_holdBodyH = 1900;
    int m_o_holdEndW  = 989;
    int m_o_holdEndH  = 50 ;
    int m_holdBodyW   = m_o_holdBodyW * m_noteZoom;
    int m_holdBodyH   = m_o_holdBodyH * m_noteZoom;
    int m_holdEndW    = m_o_holdEndW  * m_noteZoom;
    int m_holdEndH    = m_o_holdEndH  * m_noteZoom;



signals:
    void chartStarted();
    void chartPaused();
    void currentTimeChanged();
    void fpsChanged();
    void noteZoomChanged();
    void o_hitPTCWidthChanged();
};

#endif // PHIVIEWER_H
