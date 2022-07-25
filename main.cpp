#include "phisoundplayer.h"
#include "./PhiObj/functions/PhiObjCreate.h"
#include "./Widgets/resizewidget.h"
#include "./Widgets/charcolumn.h""
#include "./PhiObj/PhigrosObj/phijudgeline.h"
#include "./PhiObj/Widgets/phiviewer.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QTimer>

#ifdef QT_DEBUG
#include <QDebug>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

#ifdef QT_DEBUG
    qDebug() << "Created application";
#endif

//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);


    // Qt auto summon - create engine

    PhiSoundPlayer* phiSoundPlayer = new PhiSoundPlayer();
//    auto root = engine.rootObjects().first();

#ifdef QT_DEBUG
    qDebug() << "获取到engine的根对象";
#endif

//    auto phiViewer = root->findChild<QObject*>("phiViewer");

#ifdef QT_DEBUG
    qDebug() << "获取到phiViewer";
#endif

//    QObject::connect(phiViewer,      SIGNAL(requestSound(int)),
//                     phiSoundPlayer, SLOT  (play(int)));// solve the audio play

#ifdef QT_DEBUG
    qDebug() << "连接了QML的PhiViewer的请求播放打击音效的信号与处理信号的槽";
#endif

//    QVariant fps = phiViewer->property("fps");

#ifdef QT_DEBUG
    qDebug() << "获取到帧率";
#endif

    // C++


    PhiViewer cpp_phiViewer;

    PhiJudgeLine* jl = new PhiJudgeLine(&cpp_phiViewer);
    for(int i = 0; i < 1000; i++)
    {
        PhiNote* note    = createNote(
                    jl,
                    "tap",
                    i * 50);
    }
    for(int i = 0; i < 1000; i++)
    {
        createHold(
                    jl,
                    "",
                    i * 10);
    }

    cpp_phiViewer.pushJudgeLine(jl);
    cpp_phiViewer.show();
    cpp_phiViewer.startChart();



    // 测试自己的窗口类
//    CharColumn test;
//    test.show();




    return app.exec();
}
