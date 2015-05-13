//
// Created by ac on 15-3-14.
//

#ifndef _CG_EDGE_H_
#define _CG_EDGE_H_

#include <QVector3D>
#include "Edge.h"

class Polygon;
class Edge {

private:
    qint64 polygonId;
    qreal x;
    qreal deltaX;
    qreal deltaY;

    QVector3D higherPoint, lowerPoint;

    const Polygon *p;

public:
    Edge(QVector3D const &p1, QVector3D const &p2, Polygon const *polygon);
    Edge();

    QVector3D getLowerPoint() const;

    QVector3D getHigherPoint() const;

    void addToMap(QMap<qint32, std::vector<Edge> >&) const;

    qint64 getPolygonId() const;

    qreal getDeltaY() const;

    qreal getDeltaX() const;

    const Polygon& getPolygon() const;

    void printSelf() const;
};

#endif //_CG_EDGE_H_

