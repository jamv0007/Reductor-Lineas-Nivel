//
// Created by Jose Antonio on 16/5/22.
//

#include "Renderer.h"
#include "TriangleModel/TriangleModel.h"
#include "TriangleModel/DrawTriangleModel.h"
#include "LevelLines/DrawLevelLines.h"
#include "LevelLines/LevelLines.h"
#include <QKeyEvent>

/***
 * Instancia del patron singleton
 */
AG::Renderer* AG::Renderer::instancia = nullptr;

/***
 * Constructor
 * @param parent Padre de la ventana del Renderer
 */
AG::Renderer::Renderer(QWidget *parent): QOpenGLWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
}

/***
 * Destructor del renderer
 */
AG::Renderer::~Renderer() noexcept {

    for(int i = 0; i < modelo.size(); i++){
        delete modelo[i];
    }
    delete shader;
    delete camara;
}

/***
 * Funcion que devuelve la instancia si esta creada, sino la crea y devuleve
 * @return Puntero a la instancia
 */
AG::Renderer* AG::Renderer::getInstancia(){
    if (!instancia) {
        instancia = new Renderer();
    }

    return instancia;
}

/***
 * Funcion para dibujar el modelo
 * @param index modelo a dibujar
 */
void AG::Renderer::drawElement(int index) {
    //Segun el tipo del modelo se dibuja de una maneras u otra
    switch (modelo[index]->getTipoModelo()) {

        case TIPO_MODELO::LINE:{
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glDrawElements(GL_LINE_STRIP, modelo[index]->getIndexNumber(), GL_UNSIGNED_INT, nullptr);
            break;
        }
        case TIPO_MODELO::SLINE:{
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glDrawElements(GL_LINES, modelo[index]->getIndexNumber(), GL_UNSIGNED_INT, nullptr);
            break;
        }
        case TIPO_MODELO::POINT:{
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glEnable(GL_PROGRAM_POINT_SIZE_EXT);
            glPointSize(4);
            glDrawElements(GL_POINTS, modelo[index]->getIndexNumber(), GL_UNSIGNED_INT, nullptr);
            break;
        }
        case TIPO_MODELO::POLYGON:{
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glDrawElements(GL_LINE_LOOP, modelo[index]->getIndexNumber(), GL_UNSIGNED_INT, nullptr);
            break;
        }
        case TIPO_MODELO::WIREFRAME:{
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glDrawElements(GL_TRIANGLES, modelo[index]->getIndexNumber(), GL_UNSIGNED_INT, nullptr);
            break;
        }
        case TIPO_MODELO::PLAIN:{
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glDrawElements(GL_TRIANGLES, modelo[index]->getIndexNumber(), GL_UNSIGNED_INT, nullptr);
            break;
        }
    }
}

/**
 * Funcion que añade un nuevo modelo si no hay uno creado ya
 * id - identificador del modelo a dibujar (0 triangulo)
 * */
void AG::Renderer::addModeloEscena(Model* m) {
    modelo.push_back(m);
}

/***
 * Funcion que borra un modelo de la escena
 * @param m Modelo a eliminar
 * @return Si ha sido eliminado o no
 */
bool AG::Renderer::deleteModeloEscena(Model *m) {
    int ind = -1;
    bool find = false;
    for(int i = 0; i < modelo.size() && !find; i++){
        if(modelo[i] == m){
            ind = i;
            find = true;
        }
    }

    if(find){
        auto it = modelo.erase(modelo.begin() + ind);
        Model* model = (Model*) &it;
        delete model;
        std::cout<<ind;
    }

    return find;
}

/***
 * Función que elimina todos los modelos
 */
void AG::Renderer::deleteAllModels() {
    for(int i = 0; i < modelo.size(); i++){
        delete modelo[i];
    }

    modelo.clear();
    update();
}

/***
 * @brief Función que realiza movimiento de camara
 * @param amount Cantidad
 * @param horizontal Si es en horizontal (true) o vertical (false)
 */
void AG::Renderer::cameraMovement(float amount, bool horizontal) {
    switch (camara->getActiveMove()) {
        case MOVEMENT_TYPE::PAN: {
            if(horizontal) {

                if (amount < 0) {
                    camara->applyPanRotation(amount);
                } else {
                    camara->applyPanRotation(amount);
                }

            }
            break;
        }
        case MOVEMENT_TYPE::TILT: {
            if(!horizontal) {
                if (amount < 0) {
                    camara->applyTiltRotation(amount);
                } else {
                    camara->applyTiltRotation(amount);
                }
            }
            break;
        }
        case MOVEMENT_TYPE::DOLLY: {
            if(horizontal) {
                camara->applyDollyCamera(-amount / 10,0);
            }else{
                camara->applyDollyCamera(0, -amount / 10);
            }
            break;
        }
        case MOVEMENT_TYPE::CRANE: {
            if(!horizontal) {
                camara->applyCraneCamera(amount/10);
            }
            break;
        }
        case MOVEMENT_TYPE::ORBIT: {
            if(horizontal){
                camara->applyOrbitRotation(-amount,0);
            }else{
                camara->applyOrbitRotation(0,-amount);
            }
            break;
        }
        case MOVEMENT_TYPE::ZOOM: {
            if(!horizontal){
                camara->applyZoom((amount/10));
            }
            break;
        }
        case MOVEMENT_TYPE::NONE:{
            break;
        }
    }
}
/***
 * @brief Función que cambia el tipo de movimiento activo de la camara
 * @param movement Movimiento que se activa
 */
void AG::Renderer::setCameraMovement(MOVEMENT_TYPE movement) {
    camara->setActiveMove(movement);
}

/***
 * Funcion sobrescrita que inicializa el OpenGL
 */
void AG::Renderer::initializeGL() {


    // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
    glEnable ( GL_DEPTH_TEST );
    glEnable(GL_MULTISAMPLE);


    glClearColor (0.0f, 0.0f, 0.0f, 1.0f );

    std::cout<<this->context()->functions()->glGetString(GL_VERSION)<<std::endl;
    shader = new Shader("pag03-vs.glsl", "pag03-fs.glsl");
    glm::vec3 posicion(0,100,0);
    glm::vec3 cameraTarget(0,0,0);
    glm::vec3 up(0,1,0);
    camara = new Camera(posicion,cameraTarget,up);

}

/***
 * Funcion que se llama al redimensionar
 * @param w Nueva anchura
 * @param h Nueva Altura
 */
void AG::Renderer::resizeGL(int w, int h) {

}

/***
 * Funcion que se llama en cada refresco del pipeline
 */
void AG::Renderer::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader->activarShader();
    GLuint sp = shader->getSP();
    for(int i = 0; i < modelo.size(); i++){
        modelo[i]->activarProgram();
        glUniformMatrix4fv(glGetUniformLocation(sp, "matrizMVP"), 1, GL_FALSE, glm::value_ptr(camara->getProjectionMatrix() * camara->getViewMatrix() * modelo[i]->getMatrizModelado()));
        glUniform4fv(glGetUniformLocation(sp,"color"), 1, glm::value_ptr(modelo[i]->getColor().getVec4()));
        drawElement(i);
    }


}

/***
 * Funcion  que se llama si hay un evento al mover el ratón
 * @param event Evento
 */
void AG::Renderer::mouseMoveEvent(QMouseEvent *event) {

    //Se convierte la posicion de y a coordenadas de ventana
    double posicionConvertidaY = height() - event->pos().y();

    //Se comprueba se pulsa el boton de la rueda y no se ha actualizado el movimiento, entonces se escoge la posicion del raton
    if(middleButton && !updateMovement){
        setCameraMovement(AG::MOVEMENT_TYPE::DOLLY);
        posXM = event->pos().x();
        posYM = posicionConvertidaY;
        updateMovement = true;
    }else if(middleButton && updateMovement){
        //Si se tiene guardada la posicion se calcula la diferencia y se actualizan las posiciobnes
        setCameraMovement(AG::MOVEMENT_TYPE::DOLLY);
        double diferenceX = event->pos().x() - posXM;
        double diferenceY = posicionConvertidaY - posYM;


        cameraMovement(float(-diferenceX*10), true);

        cameraMovement(float(diferenceY*10), false);

        posXM = event->pos().x();
        posYM = posicionConvertidaY;

    }else if(!middleButton){
        updateMovement = false;
    }

    //Se comprueba si se ha pulsado el boton izquierdo y se mueve el raton
    if (botonPress && !updateValues) {
        setCameraMovement(AG::MOVEMENT_TYPE::ORBIT);
        posX = event->pos().x();
        posY = posicionConvertidaY;
        updateValues = true;


    }else if(botonPress && updateValues){
        //Si swe han almaxenado los valores iniciales y se mueve se actualizan
        setCameraMovement(AG::MOVEMENT_TYPE::ORBIT);
        double diferenceX = event->pos().x() - posX;
        double diferenceY = posicionConvertidaY - posY;


        cameraMovement(float(diferenceX / 40), true);
        cameraMovement(float(diferenceY / 40), false);

        posX = event->pos().x();
        posY = posicionConvertidaY;


    }else if(!botonPress){
        updateValues = false;


    }

    setCameraMovement(AG::MOVEMENT_TYPE::NONE);

    update();

    QWidget::mouseMoveEvent(event);
}

/***
 * Se llama al pulsar los botones del raton
 * @param event
 */
void AG::Renderer::mousePressEvent(QMouseEvent *event) {

    switch (event->button()) {
        case Qt::LeftButton:{
            botonPress = true;
        }
            break;
        case Qt::MiddleButton:{
            middleButton = true;
        }
            break;
    }


    QWidget::mousePressEvent(event);

}

/***
 * Se llama al liberar el boton del raton
 * @param event
 */
void AG::Renderer::mouseReleaseEvent(QMouseEvent *event) {

    if(event->button() == Qt::LeftButton) {
        botonPress = false;
        updateValues = false;
        posY = 0;
        posX = 0;
    }else if(event->button() == Qt::MiddleButton){
        middleButton = false;
        updateMovement = false;
        posXM = 0;
        posYM = 0;
    }


    QWidget::mouseReleaseEvent(event);
}

/***
 * Funcion que se llama al girar la rueda del raton
 * @param event
 */
void AG::Renderer::wheelEvent(QWheelEvent *event) {

    setCameraMovement(AG::MOVEMENT_TYPE::ZOOM);
    cameraMovement(-(event->angleDelta().y()/10), false);
    setCameraMovement(AG::MOVEMENT_TYPE::NONE);

    update();
}

/***
 * Funcion que resetea la camara a su estado inicial
 */
void AG::Renderer::resetCamera()  {

    glm::vec3 posicion(0,100,0);
    glm::vec3 cameraTarget(0,0,0);
    glm::vec3 up(0,1,0);
    camara->setCamera(posicion,cameraTarget,up);
    update();

}


