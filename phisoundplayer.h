#ifndef PHISOUNDPLAYER_H
#define PHISOUNDPLAYER_H

#include <QSound>
#include <QVector>
#include <QString>
#include <QObject>

class PhiSoundPlayer : public QObject
{
    Q_OBJECT
public:
    explicit PhiSoundPlayer(QObject *parent = nullptr);

signals:


public slots:
    void play(int typeIndex);


private:
    QVector<QString> soundRes = {
        ":/res/phi/sound/Tap.wav",
        ":/res/phi/sound/Drag.wav",
        ":/res/phi/sound/Flick.wav",
        ":/res/phi/sound/Tap.wav",
        ":/res/phi/sound/Tap.wav",
        ":/res/phi/sound/Drag.wav",
        ":/res/phi/sound/Flick.wav",
        ":/res/phi/sound/Tap.wav"
    };


};

#endif // PHISOUNDPLAYER_H
