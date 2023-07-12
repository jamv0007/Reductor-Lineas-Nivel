//
// Created by Jose Antonio on 15/5/22.
//

#include "Window.h"
#include <QFileDialog>

/***
 * Constructor de la ventana
 */
Window::Window(){

    //Instancian los elementos iniciales de la legenda y el slider
    legendWindow = new LegendWindow();
    legendWindow->hide();

    errorS = new QSlider(Qt::Orientation::Horizontal,this);
    errorS->setMinimum(0);
    errorS->setMaximum(1000);

    //Estructura de elementos de los layouts
    QWidget* w = new QWidget;
    setCentralWidget(w);
    QHBoxLayout* layout = new QHBoxLayout;
    QVBoxLayout* menu = new QVBoxLayout;

    menu->setAlignment(Qt::AlignTop);
    menu->setSpacing(30);

    //Titulo de la seccion de carga del terreno
    QFont title("Arial",20,QFont::Bold);
    QLabel* terrainLoad = new QLabel("Carga del terreno",this);
    terrainLoad->setAlignment(Qt::AlignCenter);
    terrainLoad->setFont(title);

    //Linea separadora
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    //Texto del archivo cargado
    QWidget* v = new QWidget;
    QFont f("Arial",16,QFont::Normal);
    fileLoad = new QLabel("Archivo cargado: No hay archivo");
    fileLoad->setFont(f);

    //Boton de seleccion de fichero
    QPushButton* selectFile = new QPushButton("Seleccionar archivo", this);
    selectFile->setStyleSheet("QPushButton{height: 45px;border-radius: 10px;font-size: 17px;color: rgb(0,0,0); background-color: rgb(245,245,245);border: none;} QPushButton:pressed{ background-color: rgb(128,128,128); }");

    //Conecta accion del boton
    QObject::connect(selectFile, &QPushButton::clicked,this,[this](){
        QString fileName = QFileDialog::getOpenFileName(this,"Abre el archivo","/");
        if(!fileName.isEmpty()) {
            //Si no hay archivo
            fileText = fileName.toStdString();
            QList<QString> f = fileName.split("/");
            QString t("Archivo cargado: ");
            QList<QString> ext = f[f.count()-1].split(".");

            //Si el archivo no tiene la extension adecuada muestra un mensaje, sino se carga
            if(ext[ext.size()-1].toStdString() == "vtk") {
                t.append(f[f.count() - 1]);
                fileLoad->setText(t);

                //Si no hay mapa
                if (!map) {
                    //Se crea y si el error es positivo se simplifica
                    std::string file = fileName.toStdString();
                    map = new LevelLines(file, scale);
                    if(error > 0.0f) {
                        map->simplifyMap(error);
                    }

                    //Se dibuja el mapa
                    drawLevelLines = new DrawLevelLines(*map);
                    AG::Renderer::getInstancia()->addModeloEscena(drawLevelLines);
                    drawLevelLines->drawItColor();

                    //Se muestra la legenda
                    std::map<float,Color> res = map->getLegend();
                    legendWindow->showWindow(res);

                } else {

                    //Si hay se cierra la legenda y el mapa y se borran, se crean unos nuevos y se muestran
                    simplify = false;
                    legendWindow->closeWindow();
                    AG::Renderer::getInstancia()->deleteAllModels();
                    drawLevelLines = nullptr;
                    delete map;
                    map = nullptr;
                    std::string file = fileName.toStdString();
                    fileText = file;
                    legendWindow->closeWindow();
                    map = new LevelLines(file, scale);
                    if(error > 0.0f){
                        errorS->setValue(0);
                    }
                    drawLevelLines = new DrawLevelLines(*map);
                    drawLevelLines->drawItColor();
                    std::map<float,Color> res = map->getLegend();
                    legendWindow->showWindow(res);


                }



            }else{
                QMessageBox::about(this, "Archivo no valido", "El archivo no tiene extension vtk");
                fileLoad->setText("Archivo cargado: No hay archivo");
            }
        }
    });


    //Desplegable de la escala del mapa
    QLabel* textoSeleccion = new QLabel("Escala del mapa:");
    textoSeleccion->setFont(f);

    QComboBox* box = new QComboBox(this);
    for(int i = 1; i < 10000; i = i * 10 ){
        std::string t = std::to_string(i);
        QString text(t.c_str());
        box->addItem(text);
    }



    //Al cambiar el elemento del desplegable
    QObject::connect(box,&QComboBox::currentTextChanged,this,[this](QString text){
       //Se obtiene la nueva escala y se cambia el maximo del valor del error
       scale = std::stod(text.toStdString());
       errorS->setMaximum(scale * pow(10,3));
       errorS->setValue(0);
       //Si hay un mapa se borra y se vuelve a crear
       if(map){
           AG::Renderer::getInstancia()->deleteAllModels();
           drawLevelLines = nullptr;
           delete map;
           map = nullptr;
           map = new LevelLines(fileText, scale);
           legendWindow->closeWindow();
           if(simplify){
               map->simplifyMap(this->error);
           }
           drawLevelLines = new DrawLevelLines(*map);
           drawLevelLines->drawItColor();
           std::map<float,Color> res = map->getLegend();
           legendWindow->showWindow(res);
       }
    });


    //Selector del error para el algoritmo
    errorMargin = new QLabel("Margen de error: 0.0");
    errorMargin->setFont(f);


    //Al mover el slider del error
    QObject::connect(errorS,&QSlider::valueChanged,this,[this](int value){
        //Se cambia el texto y se divide entre 10 para que se puedan decimales
        std::string s = "Margen de error: " + std::to_string((float)value / 10.0f);
        errorMargin->setText(s.c_str());
        this->error = (float)value / 10.0f;

        //Si hay mapa
        if(map) {
            //Si el error es 0 se resetea
            if (this->error == 0.0f) {
                //Original
                simplify = false;
                map->resetMap();

                AG::Renderer::getInstancia()->deleteAllModels();
                drawLevelLines = new DrawLevelLines(*map);
                drawLevelLines->drawItColor();


            } else {
                //Si es otro se dibuja reseteado y simplificado
                //Simplificado
                simplify = true;

                map->resetMap();
                map->simplifyMap(this->error);

                AG::Renderer::getInstancia()->deleteAllModels();
                drawLevelLines = new DrawLevelLines(*map);
                drawLevelLines->drawItColor();


            }
        }

    });


    //Espacio en blanco
    QLabel* space = new QLabel("",this);

    //Texto y linea de simplificar
    QLabel* simplify = new QLabel("Simplificar",this);
    simplify->setAlignment(Qt::AlignCenter);
    simplify->setFont(title);

    QFrame *line2 = new QFrame(this);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    //Widgets se añaden al menu lateral
    menu->addWidget(terrainLoad);
    menu->addWidget(line);
    menu->addWidget(fileLoad);
    menu->addWidget(selectFile);
    menu->addWidget(textoSeleccion);
    menu->addWidget(box);


    menu->addWidget(space);
    menu->addWidget(simplify);
    menu->addWidget(line2);
    menu->addWidget(errorMargin);
    menu->addWidget(errorS);

    //Se define la anchura maxima
    v->setLayout(menu);
    v->setMaximumWidth(this->width() / 2);

    layout->addWidget(AG::Renderer::getInstancia());
    layout->addWidget(v);
    w->setLayout(layout);


}

/***
 * Destructor de la ventana
 */
Window::~Window(){

}



/***
 * Eventos al pulsar las teclas
 * @param event evento
 */
void Window::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
        case Qt::Key_Escape:{//Al pulsar escape se cierra
            legendWindow->closeWindow();
            close();
        }
            break;
        case Qt::Key_C:{//Usar c para resetear la camara
            AG::Renderer::getInstancia()->resetCamera();
        }
        break;
    }

}




