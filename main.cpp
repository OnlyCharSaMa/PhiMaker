#include "phisoundplayer.h"
#include "./PhiObj/functions/PhiObjCreate.h"
#include "./Widgets/resizewidget.h"
#include "./Widgets/charcolumn.h""
#include "./Widgets/singleitemwidget.h"
#include "./PhiObj/PhigrosObj/phijudgeline.h"
#include "./PhiObj/PhigrosObj/phiabstractnote.h"
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
//    for(int i = 0; i < 1000; i++)
//    {
//        PhiNote* note    = createNote(
//                    jl,
//                    "tap",
//                    i * 50);
//    }
    for(int i = 0; i < 100; i++)
    {
        createHold(
                    jl,
                    "",
                    i * 1500);
    }

    cpp_phiViewer.pushJudgeLine(jl);
    cpp_phiViewer.show();
    cpp_phiViewer.startChart();



    // 测试自己的窗口类
    CharColumn test;
    test.show();
    SingleItemWidget siW;
    siW.setLabelColor(QColor(240, 240, 240, 255));
    siW.setClipLineColor(QColor(150, 150, 150, 255));
    siW.setClipLineWidth(1);
    siW.setImageWidgetRadius(5);
    test << &siW;

    SingleItemWidget siW3;
    siW3.setLabelColor(QColor(240, 240, 240, 255));
    siW3.setClipLineColor(QColor(150, 150, 150, 255));
    siW3.setClipLineWidth(1);
    siW3.setImageWidgetRadius(5);
    test << &siW3;

    SingleItemWidget siW4;
    siW4.setLabelColor(QColor(240, 240, 240, 255));
    siW4.setClipLineColor(QColor(150, 150, 150, 255));
    siW4.setClipLineWidth(1);
    siW4.setImageWidgetRadius(5);
    test << &siW4;

    SingleItemWidget siW2;
    siW2.setLabelColor(QColor(240, 240, 240, 255));
    siW2.setClipLineColor(QColor(0, 0, 0, 0));
    siW2.setImageWidgetRadius(5);
    test << &siW2;
    siW.show();
    siW2.show();
    siW3.show();
    siW4.show();




    return app.exec();
}
