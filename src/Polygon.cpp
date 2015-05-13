#include "Polygon.h"
#include "cgtype.h"
#include <iostream>
#include <cassert>

using std::vector;

qint64 Polygon::idHeader = 0;

QVector3D Polygon::computeNormal(vector<QVector3D> points) {
    QVector3D a = points[0] - points[1];
    QVector3D b = points[0] - points[2];
    return QVector3D::crossProduct(a, b);
}

QVector4D Polygon::computePlaneEquation(vector<QVector3D> points) {
    QVector3D N = computeNormal(points);
    QVector4D result = N.toVector4D();
    result.setW(-QVector3D::dotProduct(N, points[0]));
    return result;
}

Polygon::Polygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3) {
    std::cerr << "not implement" << std::endl;
}

bool myfunction(QVector3D i, QVector3D j) {
    return (i.y() > j.y());
}

Polygon::Polygon(std::vector<QVector3D> points) {
    assert(points.size() > 2);
    this->points = points;
    QVector4D abcd = computePlaneEquation(points);
    a = abcd.x();
    b = abcd.y();
    c = abcd.z();
    d = abcd.w();

    id = ++idHeader;

    std::sort(points.begin(), points.end(), myfunction);
    maxY = round(points.at(0).y());
    int minY = round(points.at(2).y());
    deltaY = maxY - minY;

    QVector3D v1(a, b, c);
    v1.normalize();
    qreal _color = QVector3D::dotProduct(v1, QVector3D(0, 0, 1));
    if(_color < 0){
        _color = - _color;
    }
    if (_color > 0.9999){
        _color = 0.9999;
    }
    color = QColor(_color * 256, _color * 256, _color * 256);

    //handle edge
    qreal xLeft = points[0].x(), xRight = points[0].x();
    for (int i = 0; i < points.size() - 1; ++i) {
        //if two point has the same y,omit it;
        if (round(points[i].y()) == round(points[i + 1].y())) {
            continue;
        }
        Edge edge = Edge(points[i], points[i + 1], this);
        edgeVector.push_back(edge);
        edge.addToMap(edges);
    }

    //if two point has the same y,omit it;
    if (round(points[0].y()) != round(points[points.size() - 1].y())) {
        //handld the edge consist of the first and the last point;
        Edge edge = Edge(points[points.size() - 1], points[0], this);
        edgeVector.push_back(edge);
        edge.addToMap(edges);
    }

    //gen random color

    //if all point has the same y, use one edge instead of the polygon
    //commit below. make this case invisible
//    if (edges.size() == 0) {
//        //find the min x and max x
//        qreal xLeft = points[0].x(), xRight = points[0].x();
//        QVector3D leftPoint = points[0], rightPoint = points[0];
//
//        for (int i = 1; i < points.size() - 1; ++i) {
//            if (points[i].x() < xLeft) {
//                xLeft = points[i].x();
//                leftPoint = points[i];
//            } else if (points[i].x() > xRight) {
//                xRight = points[i].x();
//                rightPoint = points[i];
//            }
//        }
//
//    }
}

void Polygon::transform(const QMatrix4x4 &matrix) {
    std::cerr << "not implement" << std::endl;
}

int Polygon::getMaxY() const {
    return maxY;
}


std::vector<Edge> Polygon::getEdge() {
    return edgeVector;
}

qint64 Polygon::getId() const {
    return id;
}


qreal Polygon::getA() const {
    return a;
}

qreal Polygon::getB() const {
    return b;
}


qreal Polygon::getDeltaY() const {
    return deltaY;
}


void Polygon::decDeltaY() {
    --deltaY;
}


void Polygon::addToMap(QMap<qint32, std::vector<Polygon *> > &polygonMap){
    if (!polygonMap.contains(maxY)) {
        polygonMap[maxY] = std::vector<Polygon *>();
    }
    polygonMap[maxY].push_back(this);
}

EdgeMap Polygon::getEdgeMap() const {
    return edges;
}


LinePair Polygon::getFirstLinePair(qint32 y) const {
    vector<Edge> aux = edges[y];
    assert(aux.size() == 2);
    return LinePair(aux);
}

bool Polygon::isValid() {
    return edgeVector.size() != 0;
}


qreal Polygon::getC() const {
    return c;
}


/**
* @return if delta < 0 return true; means that the polygen shoud be remova from
* activity polygon table
*/
bool Polygon::upDate(){
    decDeltaY();
    return deltaY < 0;
}

const vector<Edge> Polygon::findNextLine(qint32 height) const{
    const vector<Edge> &aux = edges[height];
    return aux;
}

EdgeMap Polygon::getEdgeMap() {
    return edges;
}

const QColor &Polygon::getColor() const {
    return color;
}
