//
// Created by Jose Antonio on 31/5/22.
//

#include "LegendWindow.h"
#include "math.h"
#include "iomanip"
#include <strstream>

/***
 * Constructor de la ventana de la legenda
 */
LegendWindow::LegendWindow(){

}

/***
 * Destructor
 */
LegendWindow::~LegendWindow(){

}

/***
 * Funcion que muestra la ventana con la legenda dados el mapa de altura-color
 * @param mapa mapa de altura-color
 */
void LegendWindow::showWindow(std::map<float, Color> &mapa) {

    this->legend = mapa;

    scale.clear();

    //Se crea el grafico iterando por los datos del mapa de altura-color
    QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();
    for(auto it = legend.begin(); it != legend.end(); it++){
        std::ostrstream out;
        out << std::fixed << std::setprecision(3) << (*it).first;
        std::string text = out.str();
        QString s(text.c_str());
        QBarSet* set = new QBarSet(s);
        set->setLabelColor(QColor(Qt::white));
        *set << 0.3;
        QColor color((*it).second.getR() * 255.0f,(*it).second.getG() * 255.0f,(*it).second.getB() * 255.0f);
        set->setColor(color);
        scale.push_back(set);
        series->append(set);

    }

    //Se crea la tabla
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Altura";
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    //Si existe se borra
    if(chartView != nullptr){
        chartView->close();
        delete chartView;
        chartView = nullptr;
    }

    //Se instancia la ventana con el grafico
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(this->size());

    //Se muestra
    chartView->show();


}

/***
 * Funcion que muestra la ventana
 */
void LegendWindow::showLegend() {
    if(chartView != nullptr) {
        chartView->show();
    }
}

/***
 * Funcion que cierra la ventana
 */
void LegendWindow::closeWindow() {
    if(chartView != nullptr) {
        chartView->hide();
    }
}