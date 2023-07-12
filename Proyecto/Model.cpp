//
// Created by Jose Antonio on 8/10/21.
//

#include "Model.h"
/**
 * Constructor del modelo
 * */
AG::Model::Model(TIPO_MODELO modelo) {
    this->modelo = modelo;
}
/**
 * Destructor del modelo
 */

AG::Model::~Model() {


    glDeleteBuffers(1,&idVBO);
    //Se borra el VAO
    glDeleteVertexArrays(1,&idVAO);

}

AG::Model::Model(const Model &orig) {
    modelo = orig.modelo;
}


/**
 * Crea el modelo del triangulo
 * */
void AG::Model::buildVAO() {

    //Se generan el numero de arrays de vertices
    glGenVertexArrays(1, &idVAO);
    glBindVertexArray(idVAO);
    //Se crean dos buffers y se asignan al id de antes
    glGenBuffers(1, &idVBO);
    //Se asigna el buffer y se lee los vertices
    glBindBuffer(GL_ARRAY_BUFFER, idVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
    glEnableVertexAttribArray(0);


    //vector de indices

    glGenBuffers(1,&idIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(GLuint),indices.data(),GL_STATIC_DRAW);
}


/**
 * Permite que se pueda activar el shader desde el renderer
 * */
void AG::Model::activarProgram() {
    glBindVertexArray(idVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,idIBO);
}

AG::TIPO_MODELO AG::Model::getTipoModelo() {
    return modelo;
}

GLuint AG::Model::getIndexNumber() {
    return indices.size();
}

AG::TypeColor AG::Model::getColor() {
    return color;
}

void AG::Model::setColor(TypeColor t) {
    color = t;
}

glm::mat4 AG::Model::getMatrizModelado() {
    return matrizModelado;
}

void AG::Model::setMatrizModelado(glm::mat4 matriz) {
    this->matrizModelado = matriz;
}

void AG::Model::setTypeModel(TIPO_MODELO type) {
    this->modelo = type;
}