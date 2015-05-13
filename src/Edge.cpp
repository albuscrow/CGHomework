//
// Created by ac on 15-3-15.
//

#include "Edge.h"
#include "Polygon.h"
#include <iostream>

void trimPoint(QVector3D& p, qreal k){
    qreal realY = p.y();
    int y = round(realY);
    p.setX(p.x() + k * (realY - y));
    p.setY(y);
}

Edge::Edge(const QVector3D &p1, const QVector3D &p2, const Polygon *polygon) {
    if (p1.y() > p2.y()) {
        higherPoint = p1;
        lowerPoint = p2;
    } else {
        higherPoint = p2;
        lowerPoint = p1;
    }
    p = polygon;
    polygonId = polygon->getId();
    x = higherPoint.x();
    if (higherPoint.y() - lowerPoint.y() == 0){
        deltaX = NAN;
    }else{
        deltaX = - (higherPoint.x() - lowerPoint.x()) / (higherPoint.y() - lowerPoint.y());
    }
    trimPoint(higherPoint, deltaX);
    trimPoint(lowerPoint, deltaX);
    deltaY = higherPoint.y() - lowerPoint.y();
}


QVector3D Edge::getHigherPoint() const{
    return higherPoint;
}

QVector3D Edge::getLowerPoint() const{
    return lowerPoint;
}

void Edge::addToMap(QMap<qint32, std::vector<Edge> > &edgeMap) const{
    if (!edgeMap.contains(higherPoint.y())){
        edgeMap[higherPoint.y()] = std::vector<Edge>();
    }
    edgeMap[higherPoint.y()].push_back(*this);
}

qint64 Edge::getPolygonId() const{
    return polygonId;
}

qreal Edge::getDeltaY() const {
    return deltaY;
}


qreal Edge::getDeltaX() const {
    return deltaX;
}

Polygon const &Edge::getPolygon() const {
    return *p;
}

Edge::Edge() {

}

void Edge::printSelf() const {
    std::cout << "height point: "<< higherPoint.x() << " "
    << higherPoint.y() << " "
    << higherPoint.z() << " " << std::endl;

    std::cout << "lower point: "<< lowerPoint.x() << " "
    << lowerPoint.y() << " "
    << lowerPoint.z() << " " << std::endl;
}
