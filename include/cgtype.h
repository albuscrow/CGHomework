//this header file used for custom type in this project

#ifndef _CG_CGTYPE_H_
#define _CG_CGTYPE_H_

//#define CG_TEST

class Polygon;
class Edge;
class LinePair;

#include <vector>
#include <QMap>
#include "tiny_obj_loader.h"


typedef std::vector<tinyobj::shape_t> SHAPES;
typedef tinyobj::shape_t SHAPE;
typedef std::vector<tinyobj::material_t> MATERIALS;
typedef tinyobj::material_t MATERIAL;
typedef QMap<qint32, std::vector<Polygon *> > PolygonMap;
typedef QMap<qint32, std::vector<Edge> > EdgeMap;

#endif
