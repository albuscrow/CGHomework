#include <QApplication>
#include <QLabel>
#include <QThread>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "objloader.h"
#include "ScanLineZBuffer.h"
#include <iostream>
#include <MainWidget.h>
#include <functional>

void print(qint32 i) {
    std::cout << i;
}

class MyThread : public QThread {
public:
    ScanLineZBuffer* scanner;
    PolygonMap* polygonMap;
    EdgeMap* edgeMap;

public:
    MyThread(){
    }

    void run() {
        scanner->raterizer(*polygonMap, *edgeMap);
    }
};

int main(int argc, char *argv[]) {

#ifndef CG_TEST
    QString filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "../../cannon.obj";
    }

    PolygonMap polygonMap;
    EdgeMap edgeMap;
    loadObj(filename, polygonMap, edgeMap);


    //UI code for test
    QApplication app(argc, argv);

    qint32 width = 800, height = 600;
    if (argc > 3) {
        bool ok;
        width = QString(argv[2]).toInt(&ok, 10);
        if (!ok) {
            width = 400;
        }

        height = QString(argv[3]).toInt(&ok, 10);
        if (!ok) {
            height = 300;
        }
    }

    MainWidget view(width, height);
    ScanLineZBuffer scanLineZBuffer(width, height);

    QObject::connect(&scanLineZBuffer, SIGNAL(updateScreenSignal(QColor * , qint32)),
            &view, SLOT(updateOneRowSlot(QColor * , qint32)));

    MyThread myThread;
    myThread.scanner = &scanLineZBuffer;
    myThread.polygonMap = &polygonMap;
    myThread.edgeMap = &edgeMap;

    myThread.start();

//    scanLineZBuffer.raterizer(polygonMap, edgeMap);
    view.show();

    return app.exec();
#else
//    test_computePlaneEquation();
    QString filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "/home/ac/code/c++/cg/test.obj";
    }

    PolygonMap polygonMap;
    EdgeMap edgeMap;
    loadObj(filename, polygonMap, edgeMap);

    ScanLineZBuffer scanLineZBuffer(300,400);
    scanLineZBuffer.raterizer(polygonMap, edgeMap);
//    qreal temp = -4321.32;
//    print(temp);

    return 0;

#endif
}






