//
// Created by ac on 15-3-15.
//

#include "LinePair.h"
#include "Polygon.h"
#include <cassert>
#include "iostream"

LinePair::LinePair(std::vector<Edge> edges) : rightLineDeltaY(0), leftLineDeltaY(0) {
    assert(edges.size() == 2);

//    qint64 polygonId;
//    qreal leftLineX, leftLineDeltaX, leftLineDeltaY;
//    qreal rightLineX, rightLineDeltaX, rightLineDeltaY;
//    qreal leftLineZ, deltaZ_X, deltaZ_Y;

    polygonId = edges[0].getPolygonId();

    if (edges[0].getHigherPoint().x() +  edges[0].getLowerPoint().x() >= edges[1].getHigherPoint().x() + edges[1].getLowerPoint().x()) {
        //edges[0] is left edge
        left = edges[0];
        right = edges[1];
    } else {
        //edges[1] is left edge
        left = edges[1];
        right = edges[0];
    }

    initMemberAboutLeft();
    initMemberAboutRight();
}

void LinePair::initMemberAboutRight() {
    rightLineX = right.getHigherPoint().x();
    rightLineDeltaX = right.getDeltaX();
    rightLineDeltaY += right.getDeltaY();
}

void LinePair::initMemberAboutLeft() {
    leftLineX = left.getHigherPoint().x();
    leftLineDeltaX = left.getDeltaX();
    leftLineDeltaY += left.getDeltaY();

    leftLineZ = left.getHigherPoint().z();

    const Polygon &polygon = left.getPolygon();
    if (polygon.getC() == 0) {
        deltaZ_X = deltaZ_Y = NAN;
    } else {
        deltaZ_X = -polygon.getA() / polygon.getC();
        deltaZ_Y = polygon.getB() / polygon.getC();
    }
}

void LinePair::decDeltaY() {
    --leftLineDeltaY;
    --rightLineDeltaY;
}

bool LinePair::updateLine(qint32 i) {
    decDeltaY();
    if (leftLineDeltaY >= 0 && rightLineDeltaY >= 0) {
        return false;
    } else if (leftLineDeltaY < 0 && rightLineDeltaY >= 0) {
        return updateLeftLine(i);
    } else if (leftLineDeltaY >= 0 && rightLineDeltaY < 0) {
        return updateRightLine(i);
    } else {
        return true;
    }
}


bool LinePair::updateLeftLine(qint32 i) {
    std::vector<Edge> vector = left.getPolygon().findNextLine(i);
    if (vector.size() == 0) {
        std::cout << leftLineDeltaY << std::endl;
        std::cout << rightLineDeltaY << std::endl;
        if(rightLineDeltaY > 0) {
            std::cout << "error" << std::endl;
        }
        if(leftLineDeltaY > 0) {
            std::cout << "error" << std::endl;
        }
        return true;
    }else{
        left = vector[0];
        initMemberAboutLeft();
        return false;
    }
}

bool LinePair::updateRightLine(qint32 i) {
    std::vector<Edge> vector = right.getPolygon().findNextLine(i);
    if (vector.size() == 0) {
        std::cout << rightLineDeltaY << std::endl;
        std::cout << leftLineDeltaY << std::endl;
        if(rightLineDeltaY > 0) {
            std::cout << "error" << std::endl;
        }
        if(leftLineDeltaY > 0) {
            std::cout << "error" << std::endl;
        }
        return true;
    } else {
        right = vector[0];
        initMemberAboutRight();
        return false;
    }
}

qreal LinePair::getLeftLineX() const{
    return leftLineX;
}

qreal LinePair::getRightLineX() const{
    return rightLineX;
}

qreal LinePair::getLeftLineDeltaX() const {
    return leftLineDeltaX;
}

qreal LinePair::getLeftLineDeltaY() const {
    return leftLineDeltaY;
}

qreal LinePair::getDetlaZ_Y() const {
    return deltaZ_Y;
}

qreal LinePair::getDetalZ_X() const {
    return deltaZ_X;
}

qreal LinePair::getLeftLineZ() const {
    return leftLineZ;
}

qreal LinePair::getRightLineDeltaY() const {
    return rightLineDeltaY;
}

qreal LinePair::getRightLineDeltaX() const {
    return rightLineDeltaX;
}

QColor LinePair::getColor() {
    return left.getPolygon().getColor();
}

void LinePair::updateParametre() {
    leftLineX += leftLineDeltaX;
    rightLineX += rightLineDeltaX;
    leftLineZ += deltaZ_Y;
}
