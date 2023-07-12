//
// Created by Jose Antonio on 15/5/22.
//

#ifndef PROYECTO_WINDOW_H
#define PROYECTO_WINDOW_H

#include "Renderer.h"
#include "LevelLines/LevelLines.h"
#include "LevelLines/DrawLevelLines.h"
#include "LegendWindow.h"
#include <QtOpenGL/QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QWindow>
#include <QtWidgets>
#include <QtOpenGLWidgets>


class Window: public QMainWindow{


    private:
        //Textos modificables de la interfaz
        QLabel* fileLoad;//Archivo cargado
        QLabel* errorMargin;//Error
        QSlider* errorS;//Slider del error

        //Instancias del mapa y del draw
        LevelLines* map = nullptr;
        DrawLevelLines* drawLevelLines = nullptr;

        //Valores
        double scale = 1;
        float error = 0.0f;
        double maxError = 1000.0;
        bool simplify = false;
        std::string fileText;

        //Instancia de la legenda
        LegendWindow* legendWindow = nullptr;

        virtual void keyPressEvent(QKeyEvent* event) override;

    public:
        Window();
        virtual ~Window();


};


#endif //PROYECTO_WINDOW_H
