#ifndef _CG_POLYGON_H_
#define _CG_POLYGON_H_

#include <QColor>
#include <QVector3D>
#include <QMatrix4x4>
#include <vector>
#include "cgtype.h"
#include "LinePair.h"

class Edge;
class Polygon{
private:
    qint64 id;
    static qint64 idHeader;

//ax + by + cz + d = 0 is the flat surface contains polygon
    qreal a, b, c, d;

    //delta in Y dimension
    int deltaY;

    //color of polygon
    QColor color;


    std::vector<QVector3D> points;

    int maxY;

    QVector3D computeNormal(std::vector<QVector3D> points);
    QVector4D computePlaneEquation(std::vector<QVector3D> points);


    EdgeMap edges;
    std::vector<Edge> edgeVector;


    /*************** private function ********************/
    void decDeltaY();

public:
    Polygon(const QVector3D &v1, const QVector3D &v2, const QVector3D &v3);

    /**
    * points size shoud be larger than 2
    */
    Polygon(const std::vector<QVector3D> points);
    void transform(const QMatrix4x4& matrix);
    int getMaxY() const;
    std::vector<Edge> getEdge();
    EdgeMap getEdgeMap();
    qint64 getId() const;
    qreal getA() const;
    qreal getB() const;
    qreal getC() const;
    qreal getDeltaY() const;
    void addToMap(QMap<qint32, std::vector<Polygon *> > &polygonMap);
    EdgeMap getEdgeMap() const;
    LinePair getFirstLinePair(qint32 y) const;

    bool isValid();
    bool upDate();
    const std::vector<Edge> findNextLine(qint32 height) const;

    const QColor& getColor() const;
};




#endif
