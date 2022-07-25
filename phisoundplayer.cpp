#include "phisoundplayer.h"
#include <QSound>

#ifdef QT_DEBUG
#include <QDebug>
#endif

PhiSoundPlayer::PhiSoundPlayer(QObject *parent)
    : QObject{parent}
{
#ifdef QT_DEBUG
    qDebug() << "PhiSoundPlayer创建完成";
#endif
}

void PhiSoundPlayer::play(int typeIndex)
{
    QSound::play(soundRes[typeIndex]);

#ifdef QT_DEBUG
    qDebug() << "播放了音效, typeIndex:" << typeIndex;
#endif

}
