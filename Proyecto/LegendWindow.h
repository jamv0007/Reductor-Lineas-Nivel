//
// Created by Jose Antonio on 31/5/22.
//

#ifndef PROYECTO_LEGENDWINDOW_H
#define PROYECTO_LEGENDWINDOW_H
#include <QtOpenGL/QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QWindow>
#include <QtWidgets>
#include <QtOpenGLWidgets>
#include <QtCharts/QtCharts>
#include "Color.h"
#include <iostream>

class LegendWindow: public QWidget {

    private:
        std::map<float,Color> legend;//Mapa con la altura y el color
        std::vector<QBarSet*> scale;//Datos de altura
        QChartView *chartView = nullptr;//Ventana con el grafico de la altura

    public:
        LegendWindow();
        virtual ~LegendWindow();
        void showWindow(std::map<float,Color> &mapa);
        void showLegend();
        void closeWindow();
};


#endif //PROYECTO_LEGENDWINDOW_H
