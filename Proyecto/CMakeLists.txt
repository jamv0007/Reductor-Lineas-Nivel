cmake_minimum_required(VERSION 3.21)
project(Proyecto)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "/Users/joseantonio/Qt/6.3.0/macos/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets Charts)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(assimp REQUIRED)
find_package(PCL 1.3 REQUIRED COMPONENTS io common search segmentation VISUALIZATION)
find_package(CGAL)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

link_directories( /usr/local/include/ )

add_executable(Proyecto main.cpp Window.cpp Window.h Renderer.cpp Renderer.h Camera.cpp Camera.h Shader.h Shader.cpp Model.h Model.cpp BasicGeometry.h Point/Point.h Point/Point.cpp Point/DrawPoint.h Point/DrawPoint.cpp AABB/AABB.h AABB/AABB.cpp AABB/DrawAABB.h AABB/DrawAABB.cpp Bezier/Bezier.h Bezier/Bezier.cpp Bezier/DrawBezier.h Bezier/DrawBezier.cpp Circle/Circle.h Circle/Circle.cpp Cloud3d/PointCloud3d.h Cloud3d/PointCloud3d.cpp Cloud3d/DrawCloud3d.h Cloud3d/DrawCloud3d.cpp Line/Line.h Line/Line.cpp Line/DrawLine.h Line/DrawLine.cpp Line3d/Line3d.h Line3d/Line3d.cpp Line3d/DrawLine3d.h Line3d/DrawLine3d.cpp Plane/Plane.h Plane/Plane.cpp Plane/DrawPlane.h Plane/DrawPlane.cpp PointCloud/PointCloud.h PointCloud/PointCloud.cpp PointCloud/DrawPointCloud.h PointCloud/DrawPointCloud.cpp Polygon/PolygonGeo.h Polygon/PolygonGeo.cpp Polygon/DrawPolygon.h Polygon/DrawPolygon.cpp Ray/RayLine.h Ray/RayLine.cpp Ray/DrawRay.h Ray/DrawRay.cpp Ray3d/Ray3d.h Ray3d/Ray3d.cpp Ray3d/DrawRay3d.h Ray3d/DrawRay3d.cpp Segment/SegmentLine.h Segment/SegmentLine.cpp Segment/DrawSegment.h Segment/DrawSegment.cpp Segment3d/Segment3d.h Segment3d/Segment3d.cpp Segment3d/DrawSegment3d.h Segment3d/DrawSegment3d.cpp Triangle/Triangle.h Triangle/Triangle.cpp Triangle/DrawTriangle.h Triangle/DrawTriangle.cpp Triangle3d/Triangle3d.h Triangle3d/Triangle3d.cpp Triangle3d/DrawTriangle3d.h Triangle3d/DrawTriangle3d.cpp TriangleModel/TriangleModel.h TriangleModel/TriangleModel.cpp TriangleModel/DrawTriangleModel.h TriangleModel/DrawTriangleModel.cpp Vect2d/Vect2d.h Vect2d/Vect2d.cpp Vect3d/Vect3d.h Vect3d/Vect3d.cpp Vect3d/DrawVect3d.h Vect3d/DrawVect3d.cpp Vertex/Vertex.h Vertex/Vertex.cpp Edge3d.h Edge3d.cpp Voxel/Voxel.cpp Voxel/Voxel.h Voxel/VoxelModel.cpp Voxel/VoxelModel.h Voxel/DrawVoxelModel.cpp Voxel/DrawVoxelModel.h Voxel/DrawVoxel.cpp Voxel/DrawVoxel.h RegularMesh3d/RegularMesh3d.cpp RegularMesh3d/RegularMesh3d.h RegularMesh3d/Box.cpp RegularMesh3d/Box.h Color.cpp Color.h TDelaunay/TDelaunay.cpp TDelaunay/TDelaunay.h ConvexHull3D/ConvexHull3D.cpp ConvexHull3D/ConvexHull3D.h LevelLines/LevelLines.cpp LevelLines/LevelLines.h LevelLines/Level.cpp LevelLines/Level.h LevelLines/DrawLevelLines.cpp LevelLines/DrawLevelLines.h LegendWindow.cpp LegendWindow.h)

target_link_libraries(Proyecto Qt6::Widgets Qt6::OpenGL glfw Qt6::OpenGLWidgets Qt6::Charts OpenGL::GL assimp::assimp ${PCL_LIBRARIES} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES} CGAL::CGAL)