#ifndef _CG_OBJLOADER_H_
#define _CG_OBJLOADER_H_


#include "cgtype.h"

qint32 loadObj(QString filename, PolygonMap &polygonMap, EdgeMap &edgeMap);


#ifdef CG_TEST

void test_computePlaneEquation();

#endif

#endif
