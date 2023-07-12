//
// Created by Jose Antonio on 10/4/22.
//

#include "DrawVoxel.h"
#include "../AABB/DrawAABB.h"

DrawVoxel::DrawVoxel(Voxel &p):voxel(p) {


}

/***
 * Dibuja el voxel del color asignado en alambre
 */
void DrawVoxel::drawIt() {
    DrawAABB* drawAabb = new DrawAABB(voxel);
    switch (voxel.getVoxel()){
        case TYPE_VOXEL::NP:
            drawAabb->drawIt(AG::TypeColor(0,0,0.5));
            break;
        case TYPE_VOXEL::GREY:
            drawAabb->drawIt(AG::TypeColor(0.5,0.5,0.5));
            break;
        case TYPE_VOXEL::BLACK:
            drawAabb->drawIt(AG::TypeColor(0,0,1));
            break;
        case TYPE_VOXEL::WHITE:
            drawAabb->drawIt(AG::TypeColor(0,0,0));
            break;
    }
}


/***
 * Dibuja plano para los grises
 */
void DrawVoxel::drawItPlaneAll() {
    DrawAABB* drawAabb = new DrawAABB(voxel);
    switch (voxel.getVoxel()){
        case TYPE_VOXEL::NP:
            drawAabb->drawIt(AG::TypeColor(0,0,0));
            break;
        case TYPE_VOXEL::GREY:
            drawAabb->drawItPlain(AG::TypeColor(1,0,0));
            break;
        case TYPE_VOXEL::BLACK:
            drawAabb->drawItPlain(AG::TypeColor(1,0,0));
            break;
        case TYPE_VOXEL::WHITE:
            drawAabb->drawIt(AG::TypeColor(0,0,0));
            break;
    }
}

/***
 * Dibuja plano pero con distinto color negros
 */
void DrawVoxel::drawItPlane() {
    DrawAABB* drawAabb = new DrawAABB(voxel);
    switch (voxel.getVoxel()){
        case TYPE_VOXEL::NP:
            drawAabb->drawIt(AG::TypeColor(0,0,0));
            break;
        case TYPE_VOXEL::GREY:
            drawAabb->drawItPlain(AG::TypeColor(1,0,0));
            break;
        case TYPE_VOXEL::BLACK:
            drawAabb->drawItPlain(AG::TypeColor(1,0,0));
            break;
        case TYPE_VOXEL::WHITE:
            drawAabb->drawIt(AG::TypeColor(0,0,0));
            break;
    }
}


