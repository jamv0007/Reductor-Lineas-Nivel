//
// Created by Jose Antonio on 1/10/21.
//

#include "Shader.h"

AG::Shader::Shader(std::string vsFile, std::string fsFile) {


    miVertexShader = "";
    miFragmentShader = "";
    ficheroFS = fsFile;
    ficheroVS = vsFile;

    //Se llama a las funciones
    try {
        cargaShaders(vsFile, fsFile);
        creaShaderProgram();
    }catch (std::runtime_error &dato){
        std::string contenido = dato.what();
        throw std::runtime_error("AG::Shader -> " + contenido);
    }
}

AG::Shader::~Shader() {
    //Eliminar los recursos de los objects

    //Se borranel fragment shader y el vertex shader
    glDeleteShader(idFS);
    glDeleteShader(idVS);

    //Se elimina el programa
    glDeleteProgram(idSP);


}

AG::Shader::Shader(const Shader &orig) {
    idVS = orig.idVS;
    idFS = orig.idFS;
    idSP = orig.idSP;


    miVertexShader = orig.miVertexShader;
    miFragmentShader= orig.miFragmentShader;

    ficheroVS = orig.ficheroVS;
    ficheroFS = orig.ficheroFS;
}

/**
 * Carga el shader del fichero correspondiente
 * */
void AG::Shader::cargaShaders(std::string vsFile, std::string fsFile) {

    std::ifstream archivoVs;
    std::ifstream archivoFs;
    std::string linea;

    archivoVs.open(vsFile,std::ios::in);

    if(!archivoVs.fail()){
        while(!archivoVs.eof()){
            std::getline(archivoVs,linea);
            miVertexShader = miVertexShader + linea + "\n";
        }

    }else{
        throw std::runtime_error("cargarShaders -> Fallo al abrir el archivo " + vsFile);
    }

    archivoVs.close();

    archivoFs.open(fsFile,std::ios::in);

    if(!archivoFs.fail()) {
        while (!archivoFs.eof()) {
            std::getline(archivoFs, linea);
            miFragmentShader = miFragmentShader + linea + "\n";
        }
    }else{
        throw std::runtime_error("cargarShaders -> Fallo al abrir el archivo " + fsFile);
    }


    archivoFs.close();
}

/**
 * Comprueba si hay errores de compilacion del shader en openGL
 * */
void AG::Shader::errorShaders() {


    GLint resultadoEnlazado = 0;
    glGetProgramiv(idSP,GL_LINK_STATUS,&resultadoEnlazado);

    if(resultadoEnlazado == GL_FALSE){

        GLint tamMsj = 0;
        std::string mensaje = "";
        glGetProgramiv(idSP,GL_INFO_LOG_LENGTH,&tamMsj);

        if(tamMsj > 0){

            GLchar* mensajeFormatoC = new GLchar[tamMsj];
            GLint datosEscritos = 0;

            glGetProgramInfoLog(idSP,tamMsj,&datosEscritos,mensajeFormatoC);
            mensaje.assign(mensajeFormatoC);

            delete[] mensajeFormatoC;
            mensajeFormatoC = nullptr;

            if(mensaje != ""){
                throw std::runtime_error("Error de los shaders -> " + mensaje);
            }

        }
    }
}

void AG::Shader::errorCompilacionShader(GLuint idShader) {
    GLint resultadoCompilacion;
    glGetShaderiv ( idShader, GL_COMPILE_STATUS, &resultadoCompilacion );

    if ( resultadoCompilacion == GL_FALSE )
    {
        // Ha habido un error en la compilación.
        // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
        GLint tamMsj = 0;
        std::string mensaje = "";
        glGetShaderiv ( idShader, GL_INFO_LOG_LENGTH, &tamMsj );
        if ( tamMsj > 0 )
        {
            GLchar* mensajeFormatoC = new GLchar[tamMsj];
            GLint datosEscritos = 0;
            glGetShaderInfoLog ( idShader, tamMsj, &datosEscritos, mensajeFormatoC );
            mensaje.assign ( mensajeFormatoC );
            delete[] mensajeFormatoC;
            mensajeFormatoC = nullptr;

            if(mensaje != ""){
                throw std::runtime_error("Error compilacion shader -> " + mensaje);
            }
        }
    }
}

/**
 * Crea y compila el shader
 * */
void AG::Shader::creaShaderProgram() {

    if(miFragmentShader == "" || miVertexShader == ""){
        throw std::runtime_error("creaShaderProgram -> No se han podido cargar los shaders");
    }

    //Se crea el vertex shader y se compila
    idVS = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* fuenteVS = miVertexShader.c_str();
    glShaderSource( idVS, 1, &fuenteVS, nullptr );
    glCompileShader( idVS );

    try {
        errorCompilacionShader(idVS);
    }catch(std::runtime_error &dato){
        std::string contenido = dato.what();
        throw std::runtime_error("creaShaderProgram -> VertexShader -> " + contenido);
    }

    //Se crean los fragments shaders y se compilan
    idFS = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fuenteFS = miFragmentShader.c_str();
    glShaderSource( idFS, 1, &fuenteFS, nullptr );
    glCompileShader( idFS );

    try{
        errorCompilacionShader(idFS);
    }catch(std::runtime_error &dato){
        std::string contenido = dato.what();
        throw std::runtime_error("creaShaderProgram -> FragmentShader -> " + contenido);
    }

    //Se crea el programa y se asignan los shadders al identificador
    idSP = glCreateProgram();
    glAttachShader(idSP,idVS);
    glAttachShader(idSP,idFS);
    glLinkProgram(idSP);

    //Se comprueba que tras ejecutar el programa hay algun  fallo con los shaders en openGL
    errorShaders();

}



/**
 * Usa el shader actual
 * */
void AG::Shader::activarShader() {

    glUseProgram(idSP);


}

GLuint AG::Shader::getSP() {
    return idSP;
}

/**
 * Getters de los nombres de los ficheros
 * */
std::string AG::Shader::getFicheroVS() {
    return ficheroVS;
}

std::string AG::Shader::getFicheroFS() {
    return ficheroFS;
}

