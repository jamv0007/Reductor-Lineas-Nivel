//
// Created by Jose Antonio on 20/2/22.
//

#include "DrawBezier.h"
#include "../Renderer.h"

DrawBezier::DrawBezier(Bezier &t,int grade): dt (t), AG::Model(AG::TIPO_MODELO::POINT){

    double tConstant = 0.02;
    int cont = 0;
    for (double i = 0.0; i < 1.0; i = i + tConstant) {
        double x = 0.0;
        double y = 0.0;
        for(int j = 0; j <= grade; j++) {
            x += binomial(grade,j) * t.getAt(j).getX() * (pow((1 - i),grade-j)) * pow(i,j);
            y += binomial(grade,j) * t.getAt(j).getY() * (pow((1 - i),grade-j)) * pow(i,j);
        }

        vertices.push_back(glm::vec3(x,y,0.0));
        indices.push_back ( cont );

        cont++;
    }


    buildVAO ();

}

int DrawBezier::binomial(int n, int m) {

    int matriz[m+1][n+1];

    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            matriz[i][j] = 0;
        }
    }

    for(int i = 0; i <= n; i++){
        matriz[0][i] = 1;
    }

    for(int i = 0; i <= m; i++){
        matriz[i][i] = 1;
    }

    for(int j = 2; j <= n; j++){
        for(int i = 1; i <= j-1; i++){
            matriz[i][j] = matriz[i-1][j-1] + matriz[i][j-1];
        }
    }

    return matriz[m][n];

}


void DrawBezier::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawBezier::drawIt (){
    AG::Renderer::getInstancia ()->addModeloEscena(this );
}