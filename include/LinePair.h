//
// Created by ac on 15-3-15.
//

#ifndef _CG_LINEPAIR_H_
#define _CG_LINEPAIR_H_

#include <QtGlobal>
#include "Edge.h"

class Edge;

class LinePair {
private:
    qint64 polygonId;
    qreal leftLineX, leftLineDeltaX, leftLineDeltaY;
    qreal rightLineX, rightLineDeltaX, rightLineDeltaY;
    qreal leftLineZ, deltaZ_X, deltaZ_Y;

    Edge left, right;


    /********************* private function ******************************/
    void decDeltaY();

    bool updateLeftLine(qint32 i);

    bool updateRightLine(qint32 i);

    void initMemberAboutLeft();

    void initMemberAboutRight();

public:
    LinePair(std::vector<Edge> edge);

    bool updateLine(qint32);

    qreal getLeftLineX() const;

    qreal getLeftLineDeltaX() const;

    qreal getLeftLineDeltaY() const;



    qreal getRightLineX() const;

    qreal getRightLineDeltaX() const;

    qreal getRightLineDeltaY() const;



    qreal getLeftLineZ() const;

    qreal getDetalZ_X() const;

    qreal getDetlaZ_Y() const;

    QColor getColor();

    void updateParametre();
};


#endif //_CG_LINEPAIR_H_
