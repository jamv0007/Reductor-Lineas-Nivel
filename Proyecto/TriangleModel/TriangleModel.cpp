
/* 
 * File:   TriangleModel.cpp
 * Author: lidia
 * 
 * Created on 20 de febrero de 2021, 10:41
 */

#include "TriangleModel.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <string>
#include <iostream>




TriangleModel::TriangleModel(const TriangleModel& orig): vv(orig.vv), vn(orig.vn), vi(orig.vi) {
}

TriangleModel::~TriangleModel() {
}



TriangleModel::TriangleModel(std::string pathFile) {
    
    try
         {
            loadFile ( pathFile );
         }
         catch ( std::runtime_error& e )
         {
            std::string mensaje = "Model -> ";
            throw std::runtime_error ( mensaje + e.what () );
         }
    
}


void TriangleModel::loadFile ( std::string pathfile )
{
   //cleaning ();
   vv.clear();
   vi.clear();
   vn.clear();

   Assimp::Importer importer;
   const aiScene* scene = importer.ReadFile ( pathfile,
                                                   aiProcess_JoinIdenticalVertices
                                                 | aiProcess_Triangulate
                                                 | aiProcess_GenSmoothNormals);
//                                                 | aiProcess_GenNormals);

   // Carga todo lo que haya en el archivo como un único modelo
   if ( !scene || !scene->mRootNode
        || ( scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ) )
   {
      std::string mensaje = "cargarArchivo: error cargando el archivo "
                            + pathfile + " -> " + importer.GetErrorString ();
      throw std::runtime_error ( mensaje );
   }

   processNodeAssimp ( scene->mRootNode, scene );

   //buildVAO ();

   //return *this;
}


/**
 * Método para procesar de manera recursiva un nodo de la estructura creada por
 * Assimp al cargar un archivo
 * @param nodo Nodo de la estructura de Assimp a procesar
 * @param escena Escena de Assimp con todo el contenido cargado del archivo
 * @note Al procesar el nodo de manera recursiva, no se garantiza que se llegue
 *       a un desbordamiento de pila
 */
void TriangleModel::processNodeAssimp ( aiNode* node, const aiScene* scene )
{
   for ( int i = 0; i < node->mNumMeshes; i++ )
   {
      //aiMesh* malla = scene->mMeshes[node->mMeshes[i]];
      // processMeshAssimp (malla, scene );
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
      processMeshAssimp ( mesh, scene );
   }

   for ( int i = 0; i < node->mNumChildren; i++ )
   {
      processNodeAssimp ( node->mChildren[i], scene );
   }
   
}


/**
 * Carga en el modelo la geometría de una malla creada por Assimp al importar
 * un archivo
 * @param malla Malla creada por Assimp
 * @param escena Escena de Assimp con todo el contenido cargado del archivo
 * @post Carga vértices, normales, coordenadas de textura (si hubiera) e índices
 */
//void TriangleModel::processMeshAssimp (  aiMesh* mesh, const aiScene* scene )
void TriangleModel::processMeshAssimp (aiMesh* mesh, const aiScene* scene )
{
   Vect3d ve, no;
   //unsigned ind;
   
   std::cout << "mNumVertices" << mesh->mNumVertices << std::endl;
   for ( int i = 0; i < mesh->mNumVertices; i++ )
   {
//      glm::vec3 v;
//      v.x = mesh->mVertices[i].x;
//      v.y = mesh->mVertices[i].y;
//      v.z = mesh->mVertices[i].z;
//      _vertices.push_back ( v );
       
      ve.setX(mesh->mVertices[i].x); 
      ve.setY(mesh->mVertices[i].y); 
      ve.setZ(mesh->mVertices[i].z); 
      vv.push_back(ve);

//      glm::vec3 n;
//      n.x = mesh->mNormals[i].x;
//      n.y = mesh->mNormals[i].y;
//      n.z = mesh->mNormals[i].z;
//      _normals.push_back ( n );
      no.setX(mesh->mNormals[i].x); 
      no.setY(mesh->mNormals[i].y); 
      no.setZ(mesh->mNormals[i].z); 
      vn.push_back(no);
      


//      if ( malla->mTextureCoords[0] )
//      {
//         glm::vec2 ct;
//         ct.x = malla->mTextureCoords[0][i].x;
//         ct.y = malla->mTextureCoords[0][i].y;
//         _cTextura.push_back ( ct );
//      }
   }

   std::cout <<"mNumFaces: " <<  mesh->mNumFaces << std::endl;
   for ( int i = 0; i < mesh->mNumFaces; i++ )
   {
      aiFace cara = mesh->mFaces[i];
      for ( int j = 0; j < cara.mNumIndices; j++ )
      {
         //_indices.push_back ( cara.mIndices[j] );
          //ind = cara.mIndices[j];
          vi.push_back(cara.mIndices[j]);
      }
   }
   
//   for (int i=0; i<vi.size(); i++){
//       std::cout << i << "->" ; 
//       std::cout << vi[i*9]<< "/"   << vi[i*9+1]<< "/" <<  vi[i*9+1]<< " "; 
//       std::cout << vi[i*9+3]<< "/" << vi[i*9+4]<< "/" <<  vi[i*9+5]<< " ";
//       std::cout << vi[i*9+6]<< "/" << vi[i*9+7]<< "/" <<  vi[i*9+8]<< std::endl;
//       
//       Triangle3d t (ve[])
//   }   
   
   std::cout <<"tamaño de ve: " <<  vv.size() << std::endl;
   std::cout <<"tamaño de vn: " <<  vn.size() << std::endl;
   std::cout <<"tamaño de vi: " <<  vi.size() << std::endl;
   
}


Triangle3d TriangleModel:: getFace(int i) {

    if (i > numTriangulos()) return (Triangle3d ());  
    
    Vect3d a = vv[vi[i*3]];
    Vect3d b = vv[vi[i*3+1]];
    Vect3d c = vv[vi[i*3+2]];
    
    return Triangle3d(a, b, c);
    }


std::vector<Triangle3d> TriangleModel::getFaces (){
    
    std::vector<Triangle3d> result;
    
    for (int i=0; i< numTriangulos(); i++){
        Vect3d a = vv[vi[i*3]];
        Vect3d b = vv[vi[i*3+1]];
        Vect3d c = vv[vi[i*3+2]];
        
        Triangle3d tri (a,b,c);
        result.push_back(tri);
    }
    return result;
}


unsigned TriangleModel:: numTriangulos (){
    
    return (unsigned) vi.size()/3;
    
    std::cout << (unsigned) vi.size()/3 << std::endl;
//    std::cout << "vn " << vn.size() << std::endl;
//    std::cout << "vv " << vv.size() << std::endl;
//    
//    return vi.size();
    
}



  PointCloud3d TriangleModel:: getCloud (){
      
      PointCloud3d pc (vv); 
      return pc; 
  }

AABB TriangleModel::getAABB() {

    PointCloud3d cloud(getCloud());
    //Vect3d min,max;

    /*float minX = INFINITY;
    float minY = INFINITY;
    float minZ = INFINITY;

    float maxX = -INFINITY;
    float maxY = -INFINITY;
    float maxZ = -INFINITY;


    for(int i = 0; i < cloud.size(); i++){
        if(cloud.getPoint(i).getX() < minX){
            minX = cloud.getPoint(i).getX();
        }
        if(cloud.getPoint(i).getY() < minY){
            minY = cloud.getPoint(i).getY();
        }
        if(cloud.getPoint(i).getZ() < minZ){
            minZ = cloud.getPoint(i).getZ();
        }
        if(cloud.getPoint(i).getX() > maxX){
            maxX = cloud.getPoint(i).getX();
        }
        if(cloud.getPoint(i).getY() > maxY){
            maxY = cloud.getPoint(i).getY();
        }
        if(cloud.getPoint(i).getZ() > maxZ){
            maxZ = cloud.getPoint(i).getZ();
        }
    }

    min.setVert(minX,minY,minZ);
    max.setVert(maxX,maxY,maxZ);*/

    AABB caja = cloud.getAABB();

    return caja;
}

bool TriangleModel::rayTraversalExh(Ray3d &r, Vect3d &p, Triangle3d &t) {

    int nearTriangle = -1;
    double distance = INFINITY;
    Vect3d point;

    std::vector<Triangle3d> triangles = this->getFaces();
    for(int i = 0; i < triangles.size(); i++){
        Triangle3d a = triangles[i];
        Vect3d v;
        if(a.rayTri(r,v)){
            double d = v.distance(p);
            if(d < distance){
                distance = d;
                nearTriangle = i;
                point = v;
            }
        }
    }

    if(nearTriangle != -1){
        t = triangles[nearTriangle];
        p = point;
        return true;
    }

    return false;
    

}

bool TriangleModel::rayTraversalExh(Ray3d &r,std::vector<Vect3d>& p, std::vector<Triangle3d>& t) {

    std::vector<Triangle3d> triangles = this->getFaces();
    for(int i = 0; i < triangles.size(); i++){
        Triangle3d a = triangles[i];
        Vect3d v;
        if(a.rayTri(r,v)){
            p.push_back(v);
            t.push_back(a);
        }
    }

    if(!t.empty()){
        return true;
    }

    return false;
}

bool TriangleModel::pointIntoMesh(Vect3d &v) {
    Vect3d origin(v);
    Vect3d a(v.getX() + 5,v.getY(),v.getZ());
    Vect3d b(v.getX() - 5,v.getY(),v.getZ());

    Ray3d oa(origin,a);
    Ray3d ob(origin,b);

    std::vector<Vect3d> p1;
    std::vector<Triangle3d> t1;

    std::vector<Vect3d> p2;
    std::vector<Triangle3d> t2;

    bool r1 = rayTraversalExh(oa,p1,t1);
    bool r2 = rayTraversalExh(ob,p2,t2);

    if(r1 && r2){
        int cont = t1.size();
        int cont2 = t2.size();

        if(cont % 2 == 0 && cont2 % 2 == 0){
            return false;
        }else if(cont % 2 != 0 && cont2 % 2 != 0){
            return true;
        }else{
            Vect3d c(v.getX(),v.getY() -5,v.getZ());
            Ray3d oc(origin,c);
            std::vector<Vect3d> p3;
            std::vector<Triangle3d> t3;
            bool r3 = rayTraversalExh(oc,p3,t3);

            if(r3){
                int cont3 = t3.size();
                if(cont3 % 2 == 0){
                    return false;
                }else{
                    return true;
                }
            }

        }
    }


    return false;
}