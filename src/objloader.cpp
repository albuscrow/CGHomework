//
// Created by ac on 15-3-15.
//
#include "objloader.h"
#include <iostream>
#include <cassert>
#include <QString>
#include <QVector3D>
#include "Polygon.h"

using std::vector;


static void PrintInfo(const std::vector<tinyobj::shape_t> &shapes, const std::vector<tinyobj::material_t> &materials) {
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
//    std::cout << "# of materials : " << materials.size() << std::endl;
//
//    for (size_t i = 0; i < shapes.size(); i++) {
//        printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
//        printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
//        printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
//        assert((shapes[i].mesh.indices.size() % 3) == 0);
//        for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
//            printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
//        }
//
//        printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
//        assert((shapes[i].mesh.positions.size() % 3) == 0);
//        for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
//            printf("  v[%ld] = (%f, %f, %f)\n", v,
//                    shapes[i].mesh.positions[3 * v + 0],
//                    shapes[i].mesh.positions[3 * v + 1],
//                    shapes[i].mesh.positions[3 * v + 2]);
//        }
//    }

}


static qreal getPositionComponent(SHAPES shapes, qint32 shapePosition, qint32 pointPosition, qint32 componentPosition) {
    return shapes[shapePosition].mesh.positions[3 * pointPosition + componentPosition];
}


qint32 loadObj(QString filename, PolygonMap &polygonMap, EdgeMap &edgeMap) {
    SHAPES shapes;
    MATERIALS materials;
    std::string err = tinyobj::LoadObj(shapes,
            materials,
            filename.toStdString().c_str(),
            NULL);
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    PrintInfo(shapes, materials);


    qreal max = std::numeric_limits<qreal>::max();
    qreal min = std::numeric_limits<qreal>::min();
    qreal maxX = min, maxY = min, minX = max, minY = max;

    for (size_t i = 0; i < shapes.size(); i++) {
        assert((shapes[i].mesh.indices.size() % 3) == 0);

        //each loop handle a polygon
        for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
            qint32 index;
            qreal x, y;
            //get three point in the specific polygon in order to computer a b c d
            for (int j = 0; j < 3; ++j) {
                index = shapes[i].mesh.indices[3 * f + j];
                x = getPositionComponent(shapes, i, index, 0);
                if (x > maxX) {
                    maxX = x;
                }
                if (x < minX){
                    minX = x;
                }
                y = getPositionComponent(shapes, i, index, 1);
                if (y > maxY) {
                    maxY = y;
                }
                if (y < minY) {
                    minY = y;
                }
            }
        }
    }

    qreal dX = 720.0 / (maxX - minX);
    qreal dY = 540.0 / (maxY - minY);
    if (dY < dX){
        dX = dY;
    }else{
        dY = dX;
    }


    for (size_t i = 0; i < shapes.size(); i++) {
        assert((shapes[i].mesh.indices.size() % 3) == 0);

        //aux var for gen polygon and edge
        std::vector<QVector3D> auxPoints(3);
        QVector3D auxPoint;
        qreal a, b, c, d;

        //each loop handle a polygon
        for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
            //reset auxpoint
            auxPoints.clear();


            qint32 index;
            qreal x, y, z;
            //get three point in the specific polygon in order to computer a b c d
            for (int j = 0; j < 3; ++j) {
                index = shapes[i].mesh.indices[3 * f + j];
                x = (getPositionComponent(shapes, i, index, 0) - minX) * dX + 40;
                y = (getPositionComponent(shapes, i, index, 1) - minY) * dY + 30;
                z = getPositionComponent(shapes, i, index, 2)*dX;
                auxPoint.setX(x);
                auxPoint.setY(y);
                auxPoint.setZ(z);
                auxPoints.push_back(auxPoint);
            }

            Polygon *polygon = new Polygon(auxPoints);
            if (polygon->isValid()) {
                //add polygon to polygon table
                polygon->addToMap(polygonMap);

                //add edge to edge table
                vector<Edge> edges = polygon->getEdge();
                for (auto edge : edges) {
                    edge.addToMap(edgeMap);
                }
            }
        }

    }
    return 0;
}


#ifdef CG_TEST

/*
void printV4(QVector4D input){
    std::cout << input.x() << " "
            << input.y() << " "
            << input.z() << " "
            << input.w() << " "<<std::endl;
}

void printV3(QVector4D input){
    std::cout << input.x() << " "
            << input.y() << " "
            << input.z() << " "<<std::endl;
}

void test_computePlaneEquation(){
    QVector3D a(1, -1, 0);
    QVector3D b(0, 1, 7);
    QVector3D c(10, 0, 1);
    vector<QVector3D> points;
    points.push_back(a);
    points.push_back(b);
    points.push_back(c);

    QVector4D abcd = computePlaneEquation(points);
    printV4(abcd);


    QVector3D temp = a * 0.3 + b * 0.3 + c * 0.4;
    printV3(temp);
    qreal temp2 = QVector3D::dotProduct(temp, abcd.toVector3D()) + abcd.w();
    std::cout << temp2 << std::endl;
    assert(temp2 == 0);
}
*/


#endif
