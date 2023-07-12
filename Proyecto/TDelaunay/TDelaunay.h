//
// Created by Jose Antonio on 3/5/22.
//

#ifndef PRACTICA6_AG_TDELAUNAY_H
#define PRACTICA6_AG_TDELAUNAY_H
#include "iostream"
#include "../PointCloud/PointCloud.h"
#include "../Triangle3d/Triangle3d.h"
#include <fstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_xy_3<K>  Gt;
typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;

typedef K::Point_3  typePoint;


class TDelaunay {
    private:
        std::vector<Triangle3d> triangles;

    public:
        TDelaunay(std::string file);
        TDelaunay(PointCloud& p);
        virtual ~TDelaunay();
        std::vector<Triangle3d> getTriangles();
};


#endif //PRACTICA6_AG_TDELAUNAY_H
