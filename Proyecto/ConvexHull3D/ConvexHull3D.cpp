//
// Created by Jose Antonio on 10/5/22.
//

#include "ConvexHull3D.h"

ConvexHull3D::ConvexHull3D(std::string file) {

    TriangleModel t(file);
    PointCloud3d p = t.getCloud();

    std::vector<Point_3> vertex;

    for(int i = 0; i < p.size(); i++){
        Point_3 point(p.getPoint(i).getX(),p.getPoint(i).getY(),p.getPoint(i).getZ());
        vertex.push_back(point);
    }

    Polyhedron_3 poly;

    CGAL::convex_hull_3(vertex.begin(),vertex.end(),poly);

    for(Polyhedron_3::Halfedge_iterator it = poly.halfedges_begin(); it != poly.halfedges_end(); it++){
        Polyhedron_3 :: Halfedge_handle h = it;
        Polyhedron_3 ::Vertex_handle  v1 = h->vertex();
        Polyhedron_3 ::Vertex_handle v2 = h->prev()->vertex();

        Vect3d vert1(v1->point().x(),v1->point().y(),v1->point().z());
        Vect3d vert2(v2->point().x(),v2->point().y(),v2->point().z());

        Segment3d s(vert1,vert2);
        triangles.push_back(s);

    }


    int a = 0;



}

ConvexHull3D::ConvexHull3D(TriangleModel &t) {

}

ConvexHull3D::~ConvexHull3D() {

}

std::vector<Segment3d> ConvexHull3D::getTriangles() {
    return triangles;
}