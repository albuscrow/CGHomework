//
// Created by ac on 15-3-15.
//

#ifndef _CG_SCANLINEBUFFER_H_
#define _CG_SCANLINEBUFFER_H_


#include <QtCore/qobject.h>
#include "LinePair.h"
#include "Polygon.h"
#include "cgtype.h"

class ScanLineZBuffer :public QObject {
Q_OBJECT
private:
    QColor *frameBuffer;
    qint32 *ZBuffer;

    //resolution ratio
    qint32 height, width;


    //input polygon and edge
    PolygonMap polygons;
    EdgeMap edges;


    //activity polygon and edge;
    std::vector<Polygon *> activityPolygon;
    std::vector<LinePair> activityEdge;


public:
    ScanLineZBuffer(qint32 width, qint32 height);

    ~ScanLineZBuffer();

    void raterizer(PolygonMap polygons, EdgeMap edgeMap);
    void setResolutionRation(qint32 width, qint32 height);
    void updateActivityPolygonAndLinePair(int i);
    void updateBuffer();
    void clearBuffer();

signals:
    void updateScreenSignal(QColor*, qint32);
};


#endif //_CG_SCANLINEBUFFER_H_

