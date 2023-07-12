//
// Created by Jose Antonio on 16/5/22.
//

#ifndef PROYECTO_RENDERER_H
#define PROYECTO_RENDERER_H


#include <QtOpenGL/QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QWindow>
#include <QtWidgets>
#include <QtOpenGLWidgets>
#include "Model.h"
#include "Camera.h"
#include "Shader.h"

namespace AG {
    class Renderer : public QOpenGLWidget {
        private:

            //Elementos de la interfaz
            std::vector<Model*> modelo;//Vector de modelos
            Shader* shader;//Instanciacion del shader
            Camera* camara;//Camara
            void drawElement(int index);
            static Renderer* instancia;//Instancia para el patron singleton
            Renderer(QWidget *parent = 0);//Constructor

            //Variables para gestion del raton
            bool botonPress = false;
            bool middleButton = false;
            bool updateValues = false;
            bool updateMovement = false;
            double posX = 0;
            double posY = 0;
            double posXM = 0;
            double posYM = 0;

    protected:
            virtual void initializeGL() override;
            virtual void resizeGL(int w, int h) override;
            virtual void paintGL() override;
            virtual void mouseMoveEvent(QMouseEvent* event) override;
            virtual void mousePressEvent(QMouseEvent* event) override;
            virtual void mouseReleaseEvent(QMouseEvent* event) override;
            virtual void wheelEvent(QWheelEvent* event) override;

        public:
            static Renderer* getInstancia();
            virtual ~Renderer();
            void cameraMovement(float amount, bool horizontal);
            void setCameraMovement(MOVEMENT_TYPE movement);
            void addModeloEscena(Model* m);
            bool deleteModeloEscena(Model* m);
            void deleteAllModels();
            void resetCamera();

    };
}


#endif //PROYECTO_RENDERER_H
