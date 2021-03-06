//
// Created by ac on 15-3-18.
//

#include "MainWidget.h"

#include <QGraphicsPixmapItem>

MainWidget::MainWidget(qint32 width, qint32 height) {
    this->width = width;
    this->height = height;

    image = new QImage(width, height, QImage::Format_ARGB32);
    QPainter painter(image);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            painter.setPen(QColor(i % 255, j % 255, i * j % 255));
            painter.drawPoint(j, i);
        }
    }
    item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene, this);
    scene->addItem(item);

}

void MainWidget::updateOneRowSlot(QColor *color, qint32 heigh) {
    QPainter painter(image);
    for (int i = 0; i < width; ++i){
        painter.setPen(color[i]);
        painter.drawPoint(i, this->height - heigh);
    }
    item->setPixmap(QPixmap::fromImage(*image));
    scene->removeItem(item);
    scene->addItem(item);
    delete []color;
}
