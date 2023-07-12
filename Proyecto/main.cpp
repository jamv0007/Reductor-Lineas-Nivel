#include <iostream>
#include <QApplication>
#include "Window.h"

int main(int argc, char*argv[]) {

    //Se crea el perfil de OpenGL
    QSurfaceFormat  surfaceFormat;
    surfaceFormat.setMajorVersion(3);
    surfaceFormat.setMinorVersion(3);
    surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    //Se crea la aplicacion de Qt
    QApplication app(argc,argv);

    //Se crea la ventana
    Window window;
    window.resize(2048,1024);
    window.show();
    window.setWindowTitle("Proyecto");

    //Se ejecuta la aplicacion
    return app.exec();
}
