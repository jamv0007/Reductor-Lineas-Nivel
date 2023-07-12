//
// Created by Jose Antonio on 10/5/22.
//

#ifndef PRACTICA6_AG_CONVEXHULL3D_H
#define PRACTICA6_AG_CONVEXHULL3D_H
#include "iostream"
#include "../TriangleModel/TriangleModel.h"
#include "../Cloud3d/PointCloud3d.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>



typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef K::Point_3 Point_3;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;


class ConvexHull3D {
    private:
        std::vector<Segment3d> triangles;
    public:
        ConvexHull3D(std::string file);
        ConvexHull3D(TriangleModel& t);
        virtual ~ConvexHull3D();
        std::vector<Segment3d> getTriangles();

};


#endif //PRACTICA6_AG_CONVEXHULL3D_H
