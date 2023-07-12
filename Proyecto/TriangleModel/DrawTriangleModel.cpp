
/* 
 * File:   DrawTriangleModel.cpp
 * Author: lidia
 * 
 * Created on 21 de febrero de 2021, 11:35
 */

#include <glm/gtx/transform.hpp>
#include "DrawTriangleModel.h"
#include "../Renderer.h"

    DrawTriangleModel::DrawTriangleModel (const TriangleModel &t): dt (t), AG::Model(AG::TIPO_MODELO::WIREFRAME){

        
       for (int i=0; i< dt.vv.size(); i++){
        
        Vect3d aux = dt.vv[i]; 
        vertices.push_back(glm::vec3 (aux.getX(), aux.getY(), aux.getZ()));

     
       }
       
       for (int i=0; i< dt.vi.size(); i++){
          
           unsigned ind = dt.vi[i];
           indices.push_back ( ind );
             
       }
     
    buildVAO ();  
        
    }
       
    
    void DrawTriangleModel::drawIt (){
     
        AG::Renderer::getInstancia()->addModeloEscena(this);

    }
    
    void DrawTriangleModel::drawIt (AG::TypeColor c){
        setColor (c);
        drawIt();
        
    }

    
    void DrawTriangleModel::drawItPlain (){
        this->modelo = AG::TIPO_MODELO::PLAIN;
        AG::Renderer::getInstancia()->addModeloEscena(this);
    }
