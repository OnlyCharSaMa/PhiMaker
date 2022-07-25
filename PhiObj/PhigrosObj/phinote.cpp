#include "phinote.h"
#include "../Widgets/phiviewer.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

PhiNote::PhiNote(QObject *parent)
    : PhiAbstractNote{parent}
{
    connect(this, SIGNAL(phiViewerChanged()),
            this, SLOT(checkTime()));

    connect(this, &PhiAbstractNote::timeChanged,
            [=](){setEndTime(time());});
}

void PhiNote::checkTime()
{
    // 以时间为标准检查是否需要将note设置为销毁状态（不绘制，并非删除）
    if( (time() - phiViewer()->currentTime()) <= 0 && !isCrashed() && isCompleted())
    {
        crash();

#ifdef QT_DEBUG
        qDebug() << "因为PhiNote的时间(" << time() << ") < currentTime("
                 << phiViewer()->currentTime() << ") 所以被销毁了";
#endif

    }
    else if( (time() - phiViewer()->currentTime()) >= 0 && isCrashed())
    {
        setIsCrashed(false);
    }
}

void PhiNote::crash()
{
    emit crashed();
    setIsCrashed(true);
    setRequestPTC(true);
    setRequestSound(true);
}





