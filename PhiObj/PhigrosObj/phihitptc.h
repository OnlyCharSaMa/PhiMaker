#ifndef PHIHITPTC_H
#define PHIHITPTC_H

#include <QObject>
#include <QTimer>

class PhiHitPTC : public QObject
{
    Q_OBJECT
public:
    explicit PhiHitPTC(
            int   ptcX,
            int   ptcY,
            qreal rotate,
            int   xOffset,
            int   imgIndex = 0,
            QObject *parent = nullptr);

    int ptcX() const;
    void setPtcX(int newPtcX);

    int ptcY() const;
    void setPtcY(int newPtcY);

    int getXOffset() const;
    void setXOffset(int newXOffset);

    qreal getRotate() const;
    void setRotate(qreal newRotate);

public slots:
    void onTimeOut();

private:
    int m_ptcX     = 0;
    int m_ptcY     = 0;
    int m_imgIndex = 0;
    int m_xOffset    = 0;
    qreal m_rotate   = 0;

signals:
    void requestHitPTC(int x, int y, qreal rotate, int xOffset, int imgIndex);
};

#endif // PHIHITPTC_H
