//
// Created by ac on 15-3-15.
//

#include "ScanLineZBuffer.h"
#include <iostream>
#include <QThread>
#include <limits>

using std::vector;

void ScanLineZBuffer::raterizer(PolygonMap polygons, EdgeMap edges) {


    this->polygons = polygons;
    this->edges = edges;

    for (int i = height; i > 0; --i) {
        clearBuffer();
        updateActivityPolygonAndLinePair(i);
        updateBuffer();

        //set signal to update screen
        QColor *temp = new QColor[width];
        memcpy(temp, frameBuffer, width * sizeof(QColor));
        emit updateScreenSignal(temp, i);
//        QThread::msleep(1);
    }

}

void ScanLineZBuffer::setResolutionRation(qint32 width, qint32 height) {
    this->width = width;
    this->height = height;
    if (frameBuffer != nullptr) {
        delete[]frameBuffer;
    }
    frameBuffer = new QColor[width];

    if (ZBuffer != nullptr) {
        delete[]ZBuffer;
    }
    ZBuffer = new qint32[width];
}

ScanLineZBuffer::ScanLineZBuffer(qint32 width, qint32 height) : frameBuffer(nullptr), ZBuffer(nullptr) {
    setResolutionRation(width, height);
}

void ScanLineZBuffer::updateActivityPolygonAndLinePair(int i) {


    //add new polygons to activityPolygon
    if (polygons.contains(i)) {
        activityPolygon.insert(activityPolygon.end(), polygons[i].begin(), polygons[i].end());
    }

    //remove polygon which is inactivity
    activityPolygon.erase(
            std::remove_if(activityPolygon.begin(), activityPolygon.end(), [this, i](Polygon *polygon) {
                bool remove = polygon->upDate();
                if (!remove) {
                    vector<Edge> edges = polygon->getEdgeMap()[i];
                    if (edges.size() == 2) {
                        activityEdge.push_back(LinePair(edges));
                    }
                }
                return remove;
            }),
            activityPolygon.end());

    //handle activity line pair
    activityEdge.erase(
            std::remove_if(activityEdge.begin(), activityEdge.end(), [i](LinePair &linePair) {
                bool removep = linePair.updateLine(i);
                return removep;
            }),
            activityEdge.end());
}

ScanLineZBuffer::~ScanLineZBuffer() {
    if (frameBuffer != nullptr) {
        delete[] frameBuffer;
    }

    if (ZBuffer != nullptr) {
        delete[] ZBuffer;
    }

}

void ScanLineZBuffer::updateBuffer() {
    for (auto &linePair : activityEdge) {

        qreal rightX = linePair.getRightLineX();
        qreal leftX = linePair.getLeftLineX();
        if (leftX > rightX) {
            rightX = linePair.getLeftLineX();
            leftX = linePair.getRightLineX();
        }

        qint32 Z = linePair.getLeftLineZ();
        qint32 DeltaZ_X = linePair.getDetalZ_X();


        QColor color = linePair.getColor();
//        QColor color(255,255,255);
//        if(rightX - leftX > 50) {
//            color = QColor((int)(rightX * leftX) % 255 ,(int)(leftX / rightX) * 255 , 0);
//        }
        for (int i = leftX; i <= rightX; ++i) {
            if (ZBuffer[i] < Z) {
                ZBuffer[i] = Z;
                frameBuffer[i] = color;
            }
            Z += DeltaZ_X;
        }
        linePair.updateParametre();
    }
}

void ScanLineZBuffer::clearBuffer() {
    for (int i = 0; i < this->width; ++i) {
        this->frameBuffer[i] = QColor(0, 0, 0);
        this->ZBuffer[i] = INT_MIN;
    }

}
